#include <CGAL/Cartesian.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Quotient.h>

#include <CGAL/Bench.h>
#include <CGAL/Bench_option_parser.h>

typedef CGAL::Quotient<CGAL::MP_Float>          NT;
typedef CGAL::Cartesian<NT>                     Kernel;

namespace po = boost::program_options;

struct Help_exception {};

template <class Kernel>
class Bench_bbox : public Kernel {
public:
  int init(void) { return 0; }
  void clean(void) {}
  void sync(void) {}
  void op(void) {}
};

typedef Bench_bbox<Kernel>                      My_bench_bbox;

int main(int argc, char * argv[])
{
  po::options_description opts("Options");
  opts.add_options()("help,h", "print help message");
  CGAL::Bench_option_parser bench_opts;
  opts.add(bench_opts.get_opts());
  po::variables_map var_map;

  try {
    po::store(po::command_line_parser(argc, argv).options(opts).run(), var_map);
    po::notify(var_map);
    if (var_map.count("help")) {
      std::cout << opts << std::endl;
      throw Help_exception();
    }
  } catch(Help_exception & /* e */) {
    return 0;
  } catch(std::exception & e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  
  CGAL::Bench<My_bench_bbox> bench("Leftturn", bench_opts.get_seconds());
  bench();
  return 0;
}
