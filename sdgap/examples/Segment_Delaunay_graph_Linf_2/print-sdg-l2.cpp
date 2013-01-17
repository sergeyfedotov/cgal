// standard includes

//#define CGAL_SDG_VERBOSE 

#ifndef CGAL_SDG_VERBOSE
#define CGAL_SDG_DEBUG(a)
#else
#define CGAL_SDG_DEBUG(a) { a }
#endif

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

// define the kernel
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Filtered_kernel.h>

typedef CGAL::Simple_cartesian<double>    CK;
typedef CGAL::Filtered_kernel<CK>         Kernel;

// typedefs for the traits and the algorithm
#include <CGAL/Segment_Delaunay_graph_traits_2.h>
#include <CGAL/Segment_Delaunay_graph_2.h>

typedef CGAL::Segment_Delaunay_graph_traits_2<Kernel>  Gt;
typedef CGAL::Segment_Delaunay_graph_2<Gt>             SDG2;

using namespace std;

int main( int argc, char *argv[] ) {
  if ( not (( argc == 1 ) or (argc == 2)) ) {
    std::cout <<"usage: "<< argv[0] <<" [filename]\n";
  }

  ifstream ifs( (argc == 1) ? "data/sites2.cin" : argv[1] );
  assert( ifs );

  SDG2          sdg;
  SDG2::Site_2  site;

  // read the sites from the stream and insert them in the diagram
  while ( ifs >> site ) { sdg.insert( site ); }

  ifs.close();


  std::cout << "About to validate diagram ..." << std::endl;

  // validate the diagram
  //assert( sdg.is_valid(true, 1) );
  cout << endl << endl;

  std::cout << "Diagram validated." << std::endl;

  sdg.file_output_verbose(std::cout);
  
  return 0;
}
