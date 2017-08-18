%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%                          plotPolyMeshDisplacements
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                   
%            Version      : 1.0                         
%            Date         : August 3, 2017  
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
%                           Copyright (c) 2017                     
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
%                                            titleResultY,titleResultNorm)
%
% Input
% =====
% meshfile : name of the file containing the polygonal mesh (string)
% dispFile : name of the file containing the nodal displacements (string)
% titleResultX : title for the plot of nodal results in the X direction (latex format)
% titleResultY : title for the plot of nodal results in the Y direction (latex format)
% titleResultNorm : title for the plot of the norm of nodal results (latex format)
%
% Output
% ======
% points        : (nx2) array containing n nodes of the polygonal mesh
% polygons      : cell array of size m, where the i-th entry contains the
%                 the connectivity of the i-th polygonal element
% displacements : (nx1) array containing the nodal displacements
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   

function [points,polygons,displacements] = ...
               plotPolyMeshDisplacements(meshFile,dispFile,titleResultX,...
                                         titleResultY,titleResultNorm)
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
  mult = 1;
  for i=1:pointsNumber
    line = fgets(dispFile);
    values = sscanf(line,'%f');
    values(2:3) = values(2:3)*mult;
    index = values(1)+1;
    displacements(index) = norm(values(2:3));
    displacementsX(index) = values(2);
    displacementsY(index) = values(3);
  end 
  %set(gcf,'Renderer','painters')
  figure; title(titleResultNorm,'Interpreter','latex','FontSize',18);
  maxNumVertices = max(cellfun(@numel,polygons));
  padFunc = @(vertList) [vertList' NaN(1,maxNumVertices-numel(vertList))];
  elements = cellfun(padFunc,polygons,'UniformOutput',false);
  elements = vertcat(elements{:});
  data = [points,displacements];
  patch('Faces',elements,'Vertices',data,...
        'FaceColor','interp','CData',displacements );
  axis('square') 
  xlim([min(points(:, 1)) - 0.5, max(points(:, 1)) + 0.5])
  ylim([min(points(:, 2)) - 2.5, max(points(:, 2)) + 2.5])  
  zlim([min(displacements) - 0.1, max(displacements) + 0.1])
  %zlim([min(displacements) - 100, max(displacements) + 100])
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
  patch('Faces',elements,'Vertices',data,...
        'FaceColor','interp','CData',displacementsX);
  axis('square')
  xlim([min(points(:,1)) - 0.5, max(points(:,1)) + 0.5])
  ylim([min(points(:,2)) - 2.5, max(points(:,2)) + 2.5])
  zlim([min(displacementsX) - 0.1, max(displacementsX) + 0.1])
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
  patch('Faces',elements,'Vertices',data,...
        'FaceColor','interp','CData',displacementsY);
  axis('square')
  xlim([min(points(:,1)) - 0.5, max(points(:,1)) + 0.5])
  ylim([min(points(:,2)) - 2.5, max(points(:,2)) + 2.5])
  zlim([min(displacementsY) - 0.1, max(displacementsY) + 0.1])
  xlabel('$x$','Interpreter','latex','FontSize',18); 
  ylabel('$y$','Interpreter','latex','FontSize',18); 
  zlabel('$u$','Interpreter','latex','FontSize',18);
  colorbar
  colormap jet
  set(gcf,'Renderer','painters')    
  set(gca, 'FontSize', 12);  
end