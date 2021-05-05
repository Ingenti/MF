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
      v = {};
      int alkub = std::max(y-hy,0);
      int alkua = std::max(x-hx,0);
      int loppub = std::min(y+hy+1,ny);
      int loppua = std::min(x+hx+1,nx);
      #pragma omp parallel for
      for(int b = alkub; b < loppub; b++)
      {
        for(int a = alkua; a < loppua; a++)
        {
          v.push_back(in[a+b*nx]);
        }
        
      }
      std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
      if(v.size() % 2 == 1)
      {
        out[x+y*nx] = v[v.size()/2];
      }
      else
      {
        out[x+y*nx] = (v[v.size()/2] + v[v.size()/2-1]) / 2;
      }
    }
  }
}
