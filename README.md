<h1> Veamy: an extensible object-oriented C++ library for the virtual element method </h1>
This repository contains the code for an open source C++ library that implements the virtual element method. The current 
release of this library allows the solution of 2D linear elastostatic problems.  

Features:
<ul>
<li> Includes its own mesher based on the computation of the constrained Voronoi
diagram. The meshes can be created in arbitrary two-dimensional domains, with or without holes, 
with procedurally generated points.</li>
<li> Meshes can also be read from OFF-style text files (an example can be found in the test folder: see "EquilibriumPatchTestMain.cpp").</li>
<li> Allows easy input of boundary conditions by constraining domain segments and nodes.</li>
<li> The results of the computation can be either written into a file or used directly. </li>
<li> PolyMesher meshes and boundary conditions can be read straightforwardly in Veamy to solve 2D linear elastostatic 
problems.</li>
</ul>

<h2>Author</h2>
<a href="https://github.com/capalvarez">Catalina Alvarez</a> -  Master's Student at Universidad de Chile.

<h2>Running a Veamy program</h2>
Veamy is currently for Unix systems only. 
<ol>
<li> Download the source code and unpack it. </li>
<li> In the root directory of Veamy, create a <b>build/</b> folder.</li>
<li> Go to <b>test/</b> folder located in the root directory of Veamy and: (a) add the main C++ file 
(say, <b>mytest.cpp</b>) containing your test example problem, (b)  modify the <b>CMakeLists.txt</b> 
by changing the file name <b>example.cpp</b> in <pre><code>set(SOURCE_FILES example.cpp)</pre></code></li> by the name 
of your main C++ file (in this case, <b>mytest.cpp</b>)
<li> Inside the <b>build/</b> folder, type and execute in the terminal:
<pre><code>cmake .. </code></pre> to create the makefiles. And to compile the program type and execute:
<pre><code>make </code></pre></li>
<li> To run your example, go to the <b>build/test/</b> folder, and in the terminal, type and execute:
<pre><code>./Test</pre></code> 
</ol>

<h2>Usage example</h2>
The complete procedure to compute the displacements using the virtual element method requires:
<ol>
<li>If using the included mesher: create the domain and the input points, and then call the meshing procedure: <br>
<pre><code>std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
Region region(points); 
region.generateSeedPoints(PointGenerator(functions::random_double(), functions::random_double()), 10, 10);
TriangleMeshGenerator generator (region.getSeedPoints(), region);
PolygonalMesh mesh = generator.getMesh();</code></pre></li>
<li>If using an externally generated mesh, for example, from PolyMesher, refer to the next section of this tutorial; for a generic mesh format see "EquilibriumPatchTestMain.cpp" in the test folder. </li>
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
<pre><code>Material* material = new MaterialPlaneStrain(1e7, 0.3);
ProblemConditions conditions(container, material);</code></pre></li>
<li>Create a Veamer instance and initialize the numerical problem: 
<pre><code>Veamer veamer;
veamer.initProblem(mesh, conditions);</code></pre></li>
<li>Compute the displacements: 
<pre><code>Eigen::VectorXd displacements = veamer.simulate(mesh);</code></pre></li>
<li>If required, print the nodal displacements to a text file:<br>
<pre><code>veamer.writeDisplacements(fileName, displacements);</code></pre></li>
<li>The results can be plotted using the Matlab function <b>plotPolyMeshDisplacements</b> (located in folder <b>/lib/visualization/</b> ):
<pre><code>[points,polygons,displacements] = plotPolyMeshDisplacements('mesh.txt','displacements.txt','$u_x^h$','$u_y^h$','$||u^h||$');</code></pre>
</ol>

This and various additional examples are provided in the <b>test/</b> folder located in the root directory of Veamy. 

<h2>Using PolyMesher</h2>
<ol>
<li>Use the Matlab function <b>PolyMesher2Veamy.m</b> included  in the <b>polymesher/</b> folder and use it to generate a Veamy-format file, whose
default name is "polymesher2veamy.txt", from PolyMesher. </li>
<li>Use the previously generated file as parameter of the <b>initProblemFromFile</b> method of the <b>Veamer</b> class. It 
requires the definition of the material properties, and, in the case the problem includes them, a body force pointer:
<pre><code>Veamer v;
Material* material = new MaterialPlaneStress(1e7, 0.3);
PolygonalMesh mesh = v.initProblemFromFile("polymesher2veamy.txt", material); </code></pre></li>
<li>Proceed exactly as shown from step 6 forward, as boundary conditions are already defined.</li>
</ol>

This and various additional examples are provided in the <b>test/</b> folder located in the root directory of Veamy. 

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

<h2>Citing Veamy</h2>
If you use Veamy in a publication, please include an acknowledgement by citing Veamy as follows: <br /><br />
A. Ortiz-Bernardin, C. Alvarez, N. Hitschfeld-Kahler, A. Russo, R. Silva, E. Olate-Sanzana. Veamy: an extensible object-oriented C++ library for the virtual element method. arXiv:1708.03438 [cs.MS]
