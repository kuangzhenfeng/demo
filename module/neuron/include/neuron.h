#ifndef __NEURON_H__
#define __NEURON_H__

#include <list>
#include <vector>

class Neuron
{
public:
    Neuron(int inputNum = 0, double value = 0);
    ~Neuron();
    double calculate();             // 计算输出值
    void update(double target);     // 更新神经元的值与权重
    void train(std::vector<int> input1, std::vector<int> input2, std::vector<int> output);      // 训练
    int test(int input1, int input2);    // 测试训练结果

    

private:
    double softmax(double x);        // 激活函数

    std::list<Neuron *> m_input;     // 连接上一神经元
    std::list<Neuron *> m_output;    // 连接下一神经元
    double m_value;                  // 神经元的自身值
    double m_weight;                 // 权重
};





#endif
