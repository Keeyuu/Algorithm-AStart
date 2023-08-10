#pragma once

#include <vector>
#include <unordered_set>
#include <queue>
#include <memory>

class INoder
{
public:
    float G = std::numeric_limits<float>::max(); // 初始化为最大值
    float H = 0;
    std::shared_ptr<INoder> Parent;

    virtual int CalcG(INoder *to) { return 0; }
    virtual float CalcH(INoder *to) { return 0; }
    virtual std::vector<std::shared_ptr<INoder>> Neighbor() { return {}; }
    virtual bool operator==(const INoder &Other) const { return false; }

    float GetF() const { return H + G; }
};

struct CompareINoder
{
    bool operator()(const std::shared_ptr<INoder> &i1, const std::shared_ptr<INoder> &i2)
    {
        return i1->GetF() > i2->GetF();
    }
};

using INoderQue = std::priority_queue<std::shared_ptr<INoder>, std::vector<std::shared_ptr<INoder>>, CompareINoder>;
using NodeSet = std::unordered_set<INoder *>;

std::vector<std::shared_ptr<INoder>> AStart(std::shared_ptr<INoder> Start, std::shared_ptr<INoder> Target)
{
    INoderQue openList;
    NodeSet closedList;
    NodeSet inOpenList;

    openList.push(Start);
    inOpenList.insert(Start.get());

    while (!openList.empty())
    {
        std::shared_ptr<INoder> currentNode = openList.top();
        openList.pop();

        if (*currentNode == *Target)
        {
            std::vector<std::shared_ptr<INoder>> path;
            while (currentNode)
            {
                path.push_back(currentNode);
                currentNode = currentNode->Parent;
            }
            return {path.rbegin(), path.rend()};
        }

        for (std::shared_ptr<INoder> neighbor : currentNode->Neighbor())
        {
            if (closedList.find(neighbor.get()) != closedList.end())
                continue; // 在关闭列表中跳过

            float tentativeG = currentNode->G + currentNode->CalcG(neighbor.get()); // 计算从当前路径到邻居节点的G

            if (inOpenList.find(neighbor.get()) == inOpenList.end() || tentativeG < neighbor->G)
            {
                neighbor->Parent = currentNode;
                neighbor->G = tentativeG;
                neighbor->H = neighbor->CalcH(Target.get());

                if (inOpenList.find(neighbor.get()) == inOpenList.end()) // 不在开放列表
                {
                    inOpenList.insert(neighbor.get()); // 入开放列表
                }
                openList.push(neighbor); // 入队列
            }
        }

        closedList.insert(currentNode.get());
        inOpenList.erase(currentNode.get());
    }

    return {}; // No path found
}
