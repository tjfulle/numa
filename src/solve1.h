#include <string>
#include <vector>
std::vector<double> solve1(std::vector<std::vector<double> > &A,
			   std::vector<double> &b,
			   std::string const method);
std::vector<double> solve_backward_sub(std::vector<std::vector<double> > &A,
				       std::vector<double> &b);
