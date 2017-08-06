<h1> Veamy: an extensible object-oriented C++ library for the virtual element method </h1>
This repository contains the code for an open source C++ library that implements the virtual element method. The first 
release of this library allows the solution of 2D linear elastostatic problems.  

Features:
<ul>
<li> Includes its own mesher based on the computation of the constrained Voronoi
diagram. The meshes can be created in arbitrary domains, with or without holes, 
with procedurally generated points.</li>
<li> Meshes can also be read from OFF-style text files (an example can be found in the test folder).</li>
<li> It allows easy input of boundary conditions by constraining domain segments and nodes.</li>
<li> The results of the computation can be either written into a file or used directly. </li>
<li> PolyMesher meshes and boundary conditions can be read straightforwardly in Veamer to solve 2D linear elastostatic 
problems.</li>
</ul>

<h2>Author</h2>
<a href="https://github.com/capalvarez">Catalina Alvarez</a> -  Master's Student at Universidad de Chile.
 
<h2>Installation</h2>
<h3>For Linux:</h3>
<li> Download the source code and unpack it. </li>
<li> Download <a href="https://www.cs.cmu.edu/~quake/triangle.html">Triangle</a>, and obtain the callable <b>triangle.o</b> object. Follow
the documentation and use:
<pre><code> make trilibrary </code></pre> 
<li> Move the file to the <b>triangle</b> folder inside the <b>lib/mesher</b> folder.</li>
<li> Once in the directory of the library, create the <b>build</b> folder. </li>
<li> Inside the <b>build</b> folder:
<pre><code>cmake ..
make</code></pre></li></ol>

<h3>For Windows:</h3>
<ol>
<li> Install Cmake for Windows and MinGW/Cygwin.</li>
<li> Download the source code and unpack it. </li>
<li> Download <a href="https://www.cs.cmu.edu/~quake/triangle.html">Triangle</a>, and obtain the callable <b>triangle.o</b> object. There are various
ways to do this, but the recommended one is to use MinGW (32 or 64 depending on your system), and use the mingw-gcc executable:
<pre><code> mingw-gcc -O -DNO_TIMER -DTRILIBRARY -c -o triangle.o triangle.c </code></pre> 
<li> Move the file to the <b>triangle</b> folder inside the <b>lib/mesher</b> folder.</li>
<li> Once in the directory of the library, create the <b>build</b> folder. </li>
<li> Inside the <b>build</b> folder, using the Command Line:
<pre><code>cmake -G "MinGW MakeFiles" ..
mingw32-make</code></pre></li></ol>


<h2>Usage example</h2>
The complete procedure to compute the displacements using Virtual Element Method requires:
<ol>
<li>If using the included mesher: create the domain and the input points, and then call the meshing procedure: <br>
<pre><code>std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
Region region(points); 
region.generateSeedPoints(PointGenerator(functions::random_double(), functions::random_double()), 10, 10);
TriangleMeshGenerator generator (region.getSeedPoints(), region);
PolygonalMesh mesh = generator.getMesh();</code></pre></li>
<li>If using an externally generated mesh: 
<li>Create a boundary conditions container and fill it as desired: <br>
<pre><code>EssentialConstraints e; NaturalConstraints n;
PointSegment leftSide (Point(0,0), Point(0,1));
Constraint leftConstraint (leftSide, mesh.getPoints(), Constraint::Direction::Total, new Constant(0));
PointSegment rightSide (Point(1,0), Point(1,1));
Constraint rightConstraint (rightSide, mesh.getPoints(), Constraint::Direction::Horizontal, new Constant(1000));
e.addConstraint(leftConstraint, mesh.getPoints());
n.addConstraint(rightConstraint, m.getPoints());
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
<pre><code>Eigen::VectorXd displacements = veamer.simulate(m);</code></pre></li>
<li>If required, print the obtained displacements to a text file:<br>
<pre><code>veamer.writeDisplacements(fileName, displacements);</code></pre></li>
</ol>

The example presented previously can be found in the test folder alongside others. 

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

