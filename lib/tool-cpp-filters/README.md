# tool-cpp-filters

Simple Moving Average and Triangular Moving Average filters

Only float, double and int types are supported

Example table using window sizes of 7 for both SMA and TMA
<img src="https://github.com/Rafdal/tool-cpp-filters/blob/main/imagen.png" alt="Filter plot"/>

|data|sma    |tma     |
|----|-------|--------|
|0   |0      |0       |
|0   |0      |0       |
|0   |0      |0       |
|0   |0      |0       |
|0   |0      |0       |
|0   |0      |0       |
|0   |0      |0       |
|0   |0      |0       |
|0   |0      |0       |
|10  |1.42857|0.204082|
|0   |1.42857|0.408163|
|10  |2.85714|0.816327|
|0   |2.85714|1.22449 |
|10  |4.28571|1.83673 |
|0   |4.28571|2.44898 |
|10  |5.71429|3.26531 |
|10  |5.71429|3.87755 |
|0   |5.71429|4.4898  |
|10  |5.71429|4.89796 |
|10  |7.14286|5.5102  |
|10  |7.14286|5.91837 |
|0   |7.14286|6.32653 |
|10  |7.14286|6.53061 |
|10  |7.14286|6.73469 |
|10  |8.57143|7.14286 |
|10  |8.57143|7.55102 |
|10  |8.57143|7.7551  |
|10  |8.57143|7.95918 |
|10  |10     |8.36735 |
|10  |10     |8.77551 |
|10  |10     |9.18367 |
|0   |8.57143|9.18367 |
|10  |8.57143|9.18367 |
|0   |7.14286|8.97959 |
|10  |7.14286|8.77551 |
|0   |5.71429|8.16326 |
|0   |4.28571|7.34694 |
|10  |4.28571|6.53061 |
|0   |4.28571|5.91837 |
|0   |2.85714|5.10204 |
|10  |4.28571|4.69388 |
|0   |2.85714|4.08163 |
|0   |2.85714|3.67347 |
|0   |2.85714|3.46939 |
|10  |2.85714|3.26531 |
|0   |2.85714|3.06122 |
|0   |2.85714|3.06122 |
|0   |1.42857|2.65306 |
|0   |1.42857|2.44898 |
|0   |1.42857|2.2449  |
|0   |1.42857|2.04082 |
|0   |0      |1.63265 |
|0   |0      |1.22449 |
|0   |0      |0.816327|
|0   |0      |0.612245|
|0   |0      |0.408163|
|0   |0      |0.204082|
|0   |0      |0       |
|0   |0      |0       |
|0   |0      |0       |


## Code example

```c++
#include <iostream>
#include <vector>

using namespace std;

vector<float> data = {
    0,0,0,0,0,0,0,0,0,10,0,
    10,0,10,0,10,10,0,10,10,
    10,0,10,10,10,10,10,10,10,
    10,10,0,10,0,10,0,0,10,0,
    0,10,0,0,0,10,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0
};

#include "SMA.h"
#include "TMA.h"

SMA<float> smaf(7);   //  N = 7
TMA<float> tmaf(7,7); //  N = 7,  M = 7  (first and second window sizes)

int main()
{
    cout << "raw,sma,tma" << endl;
    for (auto& v : data) {
    
        smaf.write(v); // O(1) complexity
        tmaf.write(v); // O(N) complexity
        cout << v << ","; 
        cout << smaf.read(); // O(N) complexity
        cout << "," << tmaf.read(); // O(M) complexity
        cout << endl;
        
        //  Note that doing a TMA write and read at the same time implies O(N+M) complexity
    }

    return 0;
}
```
