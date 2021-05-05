#include <vector>
#include <algorithm>


/*
This is the function you need to implement. Quick reference:
- input rows: 0 <= y < ny
- input columns: 0 <= x < nx
- element at row y and column x is stored in in[x + y*nx]
- for each pixel (x, y), store the median of the pixels (a, b) which satisfy
  max(x-hx, 0) <= a < min(x+hx+1, nx), max(y-hy, 0) <= b < min(y+hy+1, ny)
  in out[x + y*nx].
*/
void mf(int ny, int nx, int hy, int hx, const float *in, float *out) 
{
  std::vector<double> v;

  for(int y = 0; y < ny; y++)
  {
    for(int x = 0; x < nx; x++)
    {

      v.clear();

      for(int b = std::max(y-hy,0); b < std::min(y+hy+1,ny); b++)
      {
        for(int a = std::max(x-hx,0); a < std::min(x+hx+1,nx); a++)
        {
          v.push_back(in[a+b*nx]);
        }
      }
      
      #pragma omp parallel
      if(v.size() % 2 == 1)
      {
        std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
        out[x+y*nx] = v[v.size()/2];
      }
      else
      {
        std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
        std::nth_element(v.begin(), v.begin() + (v.size()/2)-1, v.end());
        out[x+y*nx] = (v[v.size()/2] + v[v.size()/2-1]) / 2;
      }

    }
  }

}
