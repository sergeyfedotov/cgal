// Author(s) : Dmitry Anisimov.
// We test speed of Wachspress coordinates on a set of automatically generated
// points inside a convex polygon with 16 vertices. We use inexact kernel.

#include <CGAL/Real_timer.h>

#include <CGAL/Polygon_2.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Wachspress_coordinates_2.h>

typedef CGAL::Real_timer Timer;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

typedef Kernel::FT      Scalar;
typedef Kernel::Point_2 Point;

typedef CGAL::Polygon_2<Kernel> Polygon;

typedef std::vector<Scalar> Coordinate_vector;
typedef Coordinate_vector::iterator Overwrite_iterator;

typedef CGAL::Barycentric_coordinates::Wachspress_coordinates_2<Polygon, Overwrite_iterator> Wachspress_coordinates;

using std::cout; using std::endl; using std::string;

int main()
{
    const int number_of_x_coordinates = 100000;
    const int number_of_y_coordinates = 1000;
    const int number_of_runs          = 1;

    const Scalar zero = Scalar(0);
    const Scalar one  = Scalar(1);
    const Scalar x_step = one / Scalar(number_of_x_coordinates);
    const Scalar y_step = one / Scalar(number_of_y_coordinates);

    const Point vertices[16] = { Point(zero                  , zero - y_step         ),
                                 Point(one                   , zero - y_step         ),
                                 Point(Scalar(3)  / Scalar(2), Scalar(1)  / Scalar(4)),
                                 Point(2                     , Scalar(3)  / Scalar(4)),
                                 Point(Scalar(9)  / Scalar(4), Scalar(5)  / Scalar(4)),
                                 Point(Scalar(9)  / Scalar(4), Scalar(9)  / Scalar(4)),
                                 Point(2                     , Scalar(11) / Scalar(4)),
                                 Point(Scalar(3)  / Scalar(2), Scalar(13) / Scalar(4)),
                                 Point(1                     , Scalar(7)  / Scalar(2)),
                                 Point(0                     , Scalar(7)  / Scalar(2)),
                                 Point(Scalar(-1) / Scalar(2), Scalar(13) / Scalar(4)),
                                 Point(-1                    , Scalar(11) / Scalar(4)),
                                 Point(Scalar(-5) / Scalar(4), Scalar(9)  / Scalar(4)),
                                 Point(Scalar(-5) / Scalar(4), Scalar(5)  / Scalar(4)),
                                 Point(-1                    , Scalar(3)  / Scalar(4)),
                                 Point(Scalar(-1) / Scalar(2), Scalar(1)  / Scalar(4)),
                              };
    const Polygon convex_polygon(vertices, vertices + 16);

    Wachspress_coordinates wachspress_coordinates(convex_polygon);

    Coordinate_vector coordinates;
    coordinates.resize(16);
    Overwrite_iterator it = coordinates.begin();

    Timer time_to_compute;

    double time = 0.0;
    for(int i = 0; i < number_of_runs; ++i) {

        time_to_compute.start();
        for(Scalar x = zero; x <= one; x += x_step) {
            for(Scalar y = zero; y <= one; y += y_step)
                wachspress_coordinates.compute(Point(x, y), it, CGAL::BC::ON_BOUNDED_SIDE);
        }
        time_to_compute.stop();
        
        time += time_to_compute.time();

        time_to_compute.reset();
    }
    const double mean_time = time / number_of_runs;

    cout.precision(10);
    cout << endl << "CPU time to compute Wachspress coordinates (16 vertices) = " << mean_time << " seconds." << endl << endl;
    
    return EXIT_SUCCESS;
}
