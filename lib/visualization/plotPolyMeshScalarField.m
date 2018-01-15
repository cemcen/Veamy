%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%                          plotPolyMeshScalarField
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                   
%            Version      : 1.0                         
%            Date         : January 15, 2018
%            Source code  : http://camlab.cl/research/software/veamy/
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%            Created by   : C. Alvarez, R. Silva, A. Ortiz-Bernardin 
%            E-mail       : aortizb@uchile.cl  
%            Homepage     : http://camlab.cl/alejandro
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%                          Copyright and License                               
%                          =====================                                                                                
%                           Copyright (c) 2018                     
%                       by Alejandro Ortiz-Bernardin                                                    
%                   Department of Mechanical Engineering                        
%                   University of Chile, Santiago, CHILE                        
%                           All Rights Reserved.                                
%                                                                              
%   This program is free software: you can redistribute it and/or modify
%   it under the terms of the GNU General Public License as published by
%   the Free Software Foundation, either version 3 of the License, or
%   (at your option) any later version.
%
%   This program is distributed in the hope that it will be useful,
%   but WITHOUT ANY WARRANTY; without even the implied warranty of
%   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%   GNU General Public License for more details.
%
%   You should have received a copy of the GNU General Public License
%   along with this program.  If not, see <http://www.gnu.org/licenses/>.                                         
%                                                                              
%-------------------------------------------------------------------------------
% Release notes 
% =============
% Version 1.0 (January 15, 2018): initial release of the code.
%
%-------------------------------------------------------------------------------
% References 
% ==========
% Part of this code has been taken from the plot_solution.m function provided in
% the source code of:
%
% [1] O. J. Sutton. The virtual element method in 50 lines of MATLAB.
%     Numerical Algorithms 2017; 75(4):1141�1159
%-------------------------------------------------------------------------------
% Purpose
% =======
% Plot nodal scalar field on a polygonal mesh
%
% Usage
% =====
% [points,polygons,scalarfield] = ...
%                  plotPolyMeshScalarField(meshFile,scalarfieldFile,titleResult,...
%                                          plotMeshOverResults)
%
% Input
% =====
% meshfile : name of the file containing the polygonal mesh (string)
% scalarfieldFile : name of the file containing the nodal scalar field (string)
% titleResult : title for the plot of nodal results (latex format)
% plotMeshOverResults : 'yes' or 'no'
%
% Output
% ======
% points        : (nx2) array containing n nodes of the polygonal mesh
% polygons      : cell array of size m, where the i-th entry contains the
%                 the connectivity of the i-th polygonal element
% scalarfield   : (nx1) array containing the nodal scalar field
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   

function [points,polygons,scalarfield] = ...
               plotPolyMeshScalarField(meshFile,scalarfieldFile,titleResult,...
                                       plotMeshOverResults)
  close all;
  mesh = fopen(meshFile);
  pointsNumber = sscanf(fgets(mesh),'%f');
  points = zeros(pointsNumber,2);
  for i=1:pointsNumber
    line = fgets(mesh);
    coordinates = sscanf(line,'%f');
    points(i,1) = coordinates(1); points(i,2) = coordinates(2);
  end
  segmentsNumber = sscanf(fgets(mesh),'%f');
  for i=1:segmentsNumber
    line = fgets(mesh);
  end
  polygonsNumber = sscanf(fgets(mesh),'%f');
  polygons = cell(polygonsNumber,1);
  for i=1:polygonsNumber
    line = fgets(mesh); 
    indexes = sscanf(line,'%f');
    polygons{i,1} = indexes(2:indexes(1)+1) + 1;
  end
  scalarfieldFile = fopen(scalarfieldFile);
  scalarfield = zeros(pointsNumber,1);
  for i=1:pointsNumber
    line = fgets(scalarfieldFile);
    values = sscanf(line,'%f');
    index = values(1)+1;
    scalarfield(index) = values(2);
  end 
  
  figure; title(titleResult,'Interpreter','latex','FontSize',18);
  maxNumVertices = max(cellfun(@numel,polygons));
  padFunc = @(vertList) [vertList' NaN(1,maxNumVertices-numel(vertList))];
  elements = cellfun(padFunc,polygons,'UniformOutput',false);
  elements = vertcat(elements{:});
  data = [points,scalarfield];
  if strcmp(plotMeshOverResults,'yes')
    patch('Faces',elements,'Vertices',data,...
          'FaceColor','interp','CData',scalarfield);
  else
    patch('Faces',elements,'Vertices',data,...
          'FaceColor','interp','EdgeColor','interp','CData',scalarfield);
  end  
  % axis('square') 
  axis equal;
  dx = 0; dy = 0; dz = 0;
  xlim([min(points(:, 1)) - dx, max(points(:, 1)) + dx])
  ylim([min(points(:, 2)) - dy, max(points(:, 2)) + dy])  
  zlim([min(scalarfield) - dz, max(scalarfield) + dz])
  xlabel('$x$','Interpreter','latex','FontSize',18); 
  ylabel('$y$','Interpreter','latex','FontSize',18); 
  zlabel('$u$','Interpreter','latex','FontSize',18);
  colorbar
  colormap jet
  set(gcf,'Renderer','painters')  
  set(gca, 'FontSize', 12);
end
