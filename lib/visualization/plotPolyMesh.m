%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%                              plotPolyMesh
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                   
%            Version      : 1.0                         
%            Date         : August 24, 2017  
%            Source code  : http://camlab.cl/research/software/veamy/
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%            Created by   : A. Ortiz-Bernardin 
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
% Version 1.0 (August 24, 2017): initial release of the code.
%
%-------------------------------------------------------------------------------
% References 
% ==========
% This function has been design to interact with Veamy:
%
% [1] A. Ortiz-Bernardin, C. Alvarez, N. Hitschfeld-Kahler, A. Russo, 
%     R. Silva, A. Olate-Sanzana. Veamy: an extensible object-oriented 
%     C++ library for the virtual element method. arXiv:1708.03438 [cs.MS]
%
%-------------------------------------------------------------------------------
% Purpose
% =======
% Plot a Veamy's polygonal mesh
%
% Usage
% =====
% [points,polygons] = plotPolyMesh(meshFile)
%
% Input
% =====
% meshfile : name of the file containing the polygonal mesh (string)
%
% Output
% ======
% points        : (nx2) array containing n nodes of the polygonal mesh
% polygons      : cell array of size m, where the i-th entry contains the
%                 the connectivity of the i-th polygonal element
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   

function [points,polygons] = plotPolyMesh(meshFile)
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

  %set(gcf,'Renderer','painters')
  figure; 
  maxNumVertices = max(cellfun(@numel,polygons));
  padFunc = @(vertList) [vertList' NaN(1,maxNumVertices-numel(vertList))];
  elements = cellfun(padFunc,polygons,'UniformOutput',false);
  elements = vertcat(elements{:});
  patch('Faces',elements,'Vertices',points,'FaceColor','w');
  set(gca, 'FontSize', 12);
  % axis('square')  
  axis equal; 
  axis off;
end
