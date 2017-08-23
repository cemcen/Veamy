<h1> Veamy: an extensible object-oriented C++ library for the virtual element method </h1>
This repository contains the code for an open source C++ library that implements the virtual element method. The first 
release of this library allows the solution of 2D linear elastostatic problems.  

Features:
<ul>
<li> Includes its own mesher based on the computation of the constrained Voronoi
diagram. The meshes can be created in arbitrary domains, with or without holes, 
with procedurally generated points.</li>
<li> Meshes can also be read from OFF-style text files (an example can be found in the test folder).</li>
<li> Allows easy input of boundary conditions by constraining domain segments and nodes.</li>
<li> The results of the computation can be either written into a file or used directly. </li>
<li> PolyMesher meshes and boundary conditions can be read straightforwardly in Veamer to solve 2D linear elastostatic 
problems.</li>
</ul>

<h2>Author</h2>
<a href="https://github.com/capalvarez">Catalina Alvarez</a> -  Master's Student at Universidad de Chile.

<h2>Running a Veamy program</h2>
Veamy is currently only for Unix systems. 
<ol>
<li> Download the source code and unpack it. </li>
<li> In the root directory of Veamy, create a <b>build/</b> folder.</li>
<li> To add any desired program using Veamy, the script must be in the <b>test/</b> folder. Go to the <b>test/</b> folder 
and modify the <b>CMakeLists.txt</b>, changing the
file name <b>example.cpp</b> in <pre><code>set(SOURCE_FILES example.cpp)</pre></code></li> by the name of your script. 
<li> Inside the <b>build</b> folder:
<pre><code>cmake .. </code></pre> to create the makefiles, and, to compile the program:
<pre><code>make </code></pre></li>
<li> To run your example, go to the <b>build/test/</b> folder and:
<pre><code>./Test</pre></code> 
</ol>

<h2>Usage example</h2>
The complete procedure to compute the displacements using Virtual Element Method requires:
<ol>
<li>If using the included mesher: create the domain and the input points, and then call the meshing procedure: <br>
<pre><code>std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
Region region(points); 
region.generateSeedPoints(PointGenerator(functions::random_double(), functions::random_double()), 10, 10);
TriangleMeshGenerator generator (region.getSeedPoints(), region);
PolygonalMesh mesh = generator.getMesh();</code></pre></li>
<li>If using an externally generated mesh, for example, from PolyMesher, refer to the next section of this tutorial. </li>
<li>Create a boundary conditions container and fill it as desired: <br>
<pre><code>EssentialConstraints e; NaturalConstraints n;
PointSegment leftSide (Point(0,0), Point(0,1));
Constraint leftConstraint (leftSide, mesh.getPoints(), Constraint::Direction::Total, new Constant(0));
PointSegment rightSide (Point(1,0), Point(1,1));
Constraint rightConstraint (rightSide, mesh.getPoints(), Constraint::Direction::Horizontal, new Constant(1000));
e.addConstraint(leftConstraint, mesh.getPoints());
n.addConstraint(rightConstraint, mesh.getPoints());
ConstraintsContainer container;
container.addConstraints(e, mesh);
container.addConstraints(n, mesh);</code></pre></li>
<li>Create the problem conditions container, assigning the domain material properties, the body forces if needed, and 
the boundary conditions: 
<pre><code>ProblemConditions conditions(container, Material(Materials::material::Steel));</code></pre></li>
<li>Create a Veamer instance and initialize the numerical problem: 
<pre><code>Veamer veamer;
veamer.initProblem(mesh, conditions);</code></pre></li>
<li>Compute the displacements: 
<pre><code>Eigen::VectorXd displacements = veamer.simulate(mesh);</code></pre></li>
<li>If required, print the obtained displacements to a text file:<br>
<pre><code>veamer.writeDisplacements(fileName, displacements);</code></pre></li>
<li>The results can be plotted using the Matlab function <b>plotPolyMeshDisplacements</b>:
<pre><code>[points,polygons,displacements] = plotPolyMeshDisplacements('mesh.txt','displacements.txt','$u_x^h$','$u_y^h$','$||u^h||$');</code></pre>
</ol>

The example presented previously can be found in the test folder alongside others. 

<h2>Using PolyMesher</h2>
<ol>
<li>Use the Matlab function PolyMesher2Veamy included  in the <b>polymesher</b> folder and use it to generate a Veamer-format file, which
default name is "polymesher2veamy.txt", from PolyMesher. </li>
<li>Using the previously generated file as parameter of the <b>initProblemFromFile</b> method of the <b>Veamer</b> class. It 
requires the definition of the material properties, and, in the case the problem includes them, a body force pointer:
<pre><code>Veamer v;
PolygonalMesh mesh = v.initProblemFromFile("polymesher2veamy.txt", Material(1e7,0.3)); </code></pre></li>
<li>Proceed exactly as shown from step 6 forward, as boundary conditions are already defined.</li>
</ol>

<h2>Acknowledgements</h2>
Veamy depends on three external open source libraries, whose code is included in the repository. 
<ul>
<li> <a href="https://www.cs.cmu.edu/~quake/triangle.html"> Triangle - A Two-Dimensional Quality Mesh Generator and 
Delaunay Triangulator. </a></li>
<li><a href="http://www.angusj.com/delphi/clipper.php"> Clipper - an open source freeware library for clipping and offsetting lines and polygons. </a></li>
</ul>
Linear algebra aspects are handled using:
<ul>
<li><a href="http://eigen.tuxfamily.org"> Eigen </a></li>
</ul>

<h2>License</h2>
This project is licensed under the GPL License. This program is free software; 
it can be redistributed or modified under the terms of the GNU General Public License as published by
the Free Software Foundation.

