# slave and master core discrete memory access benchmark
为证实从核没有data cache的事实，进行了测试。测试结果证明：从核离散访存对性能有影响，但影响不大。
```Master: 主存连续访问耗时：38885758
Master: 主存离散访问耗时：58507180
Slave: 片上内存连续访存：357141286
Slave: 片上内存离散访存：381085939
Slave: GLD访问主存-连续:352447783
Slave: GLD访问主存-离散:363410675
```
