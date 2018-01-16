%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%                          plotPolyMeshDisplacements
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                   
%            Version      : 1.1                         
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
%                           Copyright (c) 2017-2018                    
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
% Version 1.1 (January 15, 2018): various improvements.
% Version 1.0 (August 3, 2017): initial release of the code.
%
%-------------------------------------------------------------------------------
% References 
% ==========
% This code has been used for plots production in Ref. [1].
%
% [1] A. Ortiz-Bernardin, C. Alvarez, N. Hitschfeld-Kahler, A. Russo, 
%     R. Silva, A. Olate-Sanzana. Veamy: an extensible object-oriented 
%     C++ library for the virtual element method. arXiv:1708.03438 [cs.MS]
%
% Part of this code has been taken from the plot_solution.m function provided in
% the source code of:
%
% [2] O. J. Sutton. The virtual element method in 50 lines of MATLAB.
%     Numerical Algorithms 2017; 75(4):1141–1159
%-------------------------------------------------------------------------------
% Purpose
% =======
% Plot nodal displacements on a polygonal mesh
%
% Usage
% =====
% [points,polygons,displacements] = ...
%                  plotPolyMeshDisplacements(meshFile,dispFile,titleResultX,...
%                                            titleResultY,titleResultNorm,...
%                                            plotMeshOverResults)
%
% Input
% =====
% meshfile : name of the file containing the polygonal mesh (string)
% dispFile : name of the file containing the nodal displacements (string)
% titleResultX : title for the plot of nodal results in the X direction (latex format)
% titleResultY : title for the plot of nodal results in the Y direction (latex format)
% titleResultNorm : title for the plot of the norm of nodal results (latex format)
% plotMeshOverResults : 'yes' or 'no'
%
% Output
% ======
% points        : (nx2) array containing n nodes of the polygonal mesh
% polygons      : cell array of size m, where the i-th entry contains the
%                 the connectivity of the i-th polygonal element
% displacements : (2nx1) array containing the nodal displacements
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   

function [points,polygons,displacements] = ...
               plotPolyMeshDisplacements(meshFile,dispFile,titleResultX,...
                                         titleResultY,titleResultNorm,...
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
  dispFile = fopen(dispFile);
  displacements = zeros(pointsNumber,1);
  displacementsX = zeros(pointsNumber,1);
  displacementsY = zeros(pointsNumber,1);
  for i=1:pointsNumber
    line = fgets(dispFile);
    values = sscanf(line,'%f');
    index = values(1)+1;
    displacements(index) = norm(values(2:3));
    displacementsX(index) = values(2);
    displacementsY(index) = values(3);
  end 
 
  figure; title(titleResultNorm,'Interpreter','latex','FontSize',18);
  maxNumVertices = max(cellfun(@numel,polygons));
  padFunc = @(vertList) [vertList' NaN(1,maxNumVertices-numel(vertList))];
  elements = cellfun(padFunc,polygons,'UniformOutput',false);
  elements = vertcat(elements{:});
  data = [points,displacements];
  if strcmp(plotMeshOverResults,'yes')
    patch('Faces',elements,'Vertices',data,...
          'FaceColor','interp','CData',displacements);
  else
    patch('Faces',elements,'Vertices',data,...
          'FaceColor','interp','EdgeColor','interp','CData',displacements);
  end  
  % axis('square') 
  axis equal; 
  dx = 0; dy = 0; dz = 0;
  xlim([min(points(:, 1)) - dx, max(points(:, 1)) + dx])
  ylim([min(points(:, 2)) - dy, max(points(:, 2)) + dy])  
  zlim([min(displacements) - dz, max(displacements) + dz])
  xlabel('$x$','Interpreter','latex','FontSize',18); 
  ylabel('$y$','Interpreter','latex','FontSize',18); 
  zlabel('$u$','Interpreter','latex','FontSize',18);
  colorbar
  colormap jet
  set(gcf,'Renderer','painters')    
  set(gca, 'FontSize', 12);

  figure; title(titleResultX,'Interpreter','latex','FontSize',18);
  maxNumVertices = max(cellfun(@numel,polygons));
  padFunc = @(vertList) [vertList' NaN(1,maxNumVertices-numel(vertList))];
  elements = cellfun(padFunc,polygons,'UniformOutput',false);
  elements = vertcat(elements{:});
  data = [points,displacementsX];
  if strcmp(plotMeshOverResults,'yes')
    patch('Faces',elements,'Vertices',data,...
          'FaceColor','interp','CData',displacementsX);
  else
    patch('Faces',elements,'Vertices',data,...
          'FaceColor','interp','EdgeColor','interp','CData',displacementsX);
  end  
  % axis('square') 
  axis equal;
  dx = 0; dy = 0; dz = 0;
  xlim([min(points(:, 1)) - dx, max(points(:, 1)) + dx])
  ylim([min(points(:, 2)) - dy, max(points(:, 2)) + dy])  
  zlim([min(displacementsX) - dz, max(displacementsX) + dz])
  xlabel('$x$','Interpreter','latex','FontSize',18); 
  ylabel('$y$','Interpreter','latex','FontSize',18); 
  zlabel('$u$','Interpreter','latex','FontSize',18);
  colorbar
  colormap jet
  set(gcf,'Renderer','painters')  
  set(gca, 'FontSize', 12);

  figure; title(titleResultY,'Interpreter','latex','FontSize',18);
  maxNumVertices = max(cellfun(@numel,polygons));
  padFunc = @(vertList) [vertList' NaN(1,maxNumVertices-numel(vertList))];
  elements = cellfun(padFunc,polygons,'UniformOutput',false);
  elements = vertcat(elements{:});
  data = [points,displacementsY];
  if strcmp(plotMeshOverResults,'yes')
    patch('Faces',elements,'Vertices',data,...
          'FaceColor','interp','CData',displacementsY);
  else
    patch('Faces',elements,'Vertices',data,...
          'FaceColor','interp','EdgeColor','interp','CData',displacementsY);
  end  
  % axis('square') 
  axis equal;
  dx = 0; dy = 0; dz = 0;
  xlim([min(points(:, 1)) - dx, max(points(:, 1)) + dx])
  ylim([min(points(:, 2)) - dy, max(points(:, 2)) + dy])  
  zlim([min(displacementsY) - dz, max(displacementsY) + dz])
  xlabel('$x$','Interpreter','latex','FontSize',18); 
  ylabel('$y$','Interpreter','latex','FontSize',18); 
  zlabel('$u$','Interpreter','latex','FontSize',18);
  colorbar
  colormap jet
  set(gcf,'Renderer','painters')    
  set(gca, 'FontSize', 12);  
end
