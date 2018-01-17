<h1> Veamy: an extensible object-oriented C++ library for the virtual element method </h1>
This repository contains the code for an open source C++ library that implements the virtual element method. The current 
release of this library allows the solution of 2D linear elastostatic problems and the 2D Poisson problem. The 2D linear elastostatic problem can also be solved using the standard three-node finite element. For this, a module called Feamy is available within Veamy.

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
Veamy is currently for Unix-like systems only. 
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
TriangleVoronoiGenerator generator (region.getSeedPoints(), region);
Mesh&ltPolygon&gt mesh = generator.getMesh();</code></pre></li>
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
<li>Create the problem conditions container (a Conditions instance), assigning the domain material properties, the body forces if needed, and 
the boundary conditions: 
<pre><code>Material* material = new MaterialPlaneStrain(1e7, 0.3);
Conditions conditions(container, material);</code></pre></li>
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
In addition, thanks to its extensibility, Veamy is capable of solving the two dimensional Poisson problem. An example is provided in the <b>test/</b> folder.

<h2>Using the Finite Element Method </h2>
Veamy, being an extensible library, includes the possibility of solving the linear elasticity problem using the Finite Element Method in a module named Feamy. Solving the linear elasticity problem using FEM is similar to VEM, with just a few differences:
<li> For now, the Finite Element Method only accepts triangular meshes (triangular elements). Triangulations 
can be generated using the same mesher used for the polygonal mesh generation, as follows:<br>
<pre><code>std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
Region region(points); 
region.generateSeedPoints(PointGenerator(functions::random_double(), functions::random_double()), 10, 10);
TriangleDelaunayGenerator generator (region.getSeedPoints(), region);
Mesh&ltTriangle&gt mesh = generator.getConformingDelaunayTriangulation();</code></pre></li>
<li>Both the constraints and problem conditions (body forces and material properties) are set exactly as in Veamy. </li>
<li>Create a Feamer instance, an ElementConstructor (which represents the type of elements that will be used for the problem. In our example,
we use linear triangular elements), and initialize the numerical problem: 
<pre><code>Feamer feamer;
feamer.initProblem(mesh, conditions, new Tri3Constructor());</code></pre></li>
<li> Obtaining the displacements and the post processing is exactly as in Veamy </li>

<h2>Using PolyMesher</h2>
<ol>
<li>Use the Matlab function <b>PolyMesher2Veamy.m</b> included  in the <b>polymesher/</b> folder and use it to generate a Veamy-format file, whose
default name is "polymesher2veamy.txt", from PolyMesher. </li>
<li>Use the previously generated file as parameter of the <b>initProblemFromFile</b> method of the <b>Veamer</b> class. It 
requires the definition of the material properties, and, in the case the problem includes them, a body force pointer:
<pre><code>Veamer v;
Material* material = new MaterialPlaneStress(1e7, 0.3);
Mesh&ltPolygon&gt mesh = v.initProblemFromFile("polymesher2veamy.txt", material); </code></pre></li>
<li>Proceed exactly as shown from step 6 forward, as boundary conditions are already defined.</li>
</ol>

This and various additional examples are provided in the <b>test/</b> folder located in the root directory of Veamy. 

<h2>Acknowledgements</h2>
Veamy depends on two external open source libraries, whose codes are included in this repository, inside <b>lib</b> folder. 
<ul>
<li><a href="https://github.com/capalvarez/Delynoi"> Delynoi: an object-oriented C++ library for the generation of polygonal meshes </a></li>
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
