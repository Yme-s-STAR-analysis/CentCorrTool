# Centrality Correction Utility

author: yghuang

version: 7.0

## Change log

30.08.2024 by yghuang (v7.0):

> Important: centrality bin splitting should be `[low, high)` instead of previous `(low, high]`
>
> The vz correction for normal mode now also add a random float to form an integer, which might not be used but impleted

04.04.2024 by yghuang (v6.1):

> Fix some bugs from unit test

04.04.2024 by yghuang (v6.0):

> To use Ashish's parameters, `CentParams.h` is changed, and please call `EnableIndianMethod(true)` before `ReadParams()`, and interfaces are changed for Indian method

23.01.2023 by yghuang (v5.0):

> Now, luminosity correction and vz correction will also consider RefMult3 or RefMult3X.
>
>> And GetRefMult3Corr would ask for an additional boolean: false for traditional RefMult3 (which is default) and true for using Refmult3X.
>
> Patch checking machanism: in CentParams header and CentCorrTool, there will be patch number, if they do not match, it will be reported.

22.11.2023 by yghuang (v4.0):

> Do pile-up correction for separate pile-up quantities.
>
>> Now support vz-dependent pile-up (related to official cuts).

09.10.2023 by yghuang (v3.1):

> New pile-up method, see X2PileUp and X4Vz.
>
> Will load bin edge when read parameters.

10.08.2023 by yghuang (v2.1):

> Important: if we want to include `Conf.h` in multi-code files, parameters there should be static.
>
> Add a centrality bin edge into Conf.h.

07.08.2023 by yghuang (v2.0):

> New version, now use `Conf.h` to contain the correction parameters.
