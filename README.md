# Minimum-Feedback-Arc-Set-Problem
本项目用于完成冯剑琳《高级算法设计与分析》的作业《最小反馈弧集合问题》

本项目相关论文《Computing a Feedback Arc Set Using PageRank》，看课件更轻松一些。将主要用c++实现。

多人开发建议使用分支操作，详细参考[多人协作教程](https://www.liaoxuefeng.com/wiki/896043488029600/900375748016320)。

### git 相关命令

```python
git branch # 查看分支状态
git checkout -b <dev> origin/<dev> # 本地关联远程分支<dev>
git checkout <dev> # 切换分支<dev>

# 提交三板斧
git add filename 
git commit -m "add env"
git push origin dev # 提交到dev分支

git pull # 如果提示冲突用这个命令
```

### 代码运行

```
bash run.sh
```

### 目录文件说明

1. ```run.sh```是运行的脚本文件，运行即可启动所有算法，输出相关结果；
2. ```data```目录存放算法运行的数据集；
3. ```head_file```目录存放头文件；
4. ```data_structure```存放算法的底层数据结构的实现，主要是邻接矩阵和图；
5. ```.out```文件即是生成的可执行文件；
6. ```utils.cpp```记录了一些共用的工具函数；
7. ```GreedyFAS.cpp```实现了贪心算法，```SortFAS```实现了排序算法；

### 其它

有问题方便的话可以写到project的issue中作为记录。

