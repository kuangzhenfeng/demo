#include "myNeuron.h"
#include <stdio.h>
#include <math.h>
#include <algorithm>

static const double studySpeed = 0.1;   // 学习率

MyNeuron::MyNeuron(int inputNum, double value) : m_value(value)
{
    for(int i = 0; i < inputNum; ++i)
    {
        MyNeuron *neu = new MyNeuron();
        m_input.push_back(neu);
        neu->m_output.push_back(this);
    }
}

MyNeuron::~MyNeuron()
{

}

double MyNeuron::calculate()
{
    double res = m_value;
    std::list<MyNeuron *>::iterator ite;
    for(ite = m_input.begin(); ite != m_input.end(); ++ite)
    {
        res += (*ite)->calculate() * (*ite)->m_weight;
    }
    // return softmax(res);
    return res;
}

void MyNeuron::update(double target)
{
    double current = calculate();
    if(current == target)
    {
        printf("OK\n");
        return;
    }
    printf("calibrate, current=%.2lf target=%.2lf ", current, target);
    std::list<MyNeuron *>::iterator ite;
    for(ite = m_input.begin(); ite != m_input.end(); ++ite)
    {
        (*ite)->m_weight += studySpeed * (target - current);
        printf("weight=%lf ", (*ite)->m_weight);
        // (*ite)->update((*ite)->calculate() * (*ite)->m_weight);      // TODO: 修正前面分支
    }
    printf("\n");
}

double MyNeuron::softmax(double x)
{
    const int choose = 0;
    double res = 0;
    switch(choose)
    {
        case 0: // Sigmoid
            return 1 / (1 + exp(-x));
        case 1: // Tanh
            return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
        case 2: // Relu
            return std::max(0.0, x);
    }
    
}

void MyNeuron::train(std::vector<int> input1, std::vector<int> input2, std::vector<int> output)
{
    for(int i = 0; i < output.size(); ++i)
    {
        m_input.front()->m_value = input1[i];
        m_input.back()->m_value = input2[i];
        update(output[i]);
    }

}

int MyNeuron::test(int input1, int input2)
{
    m_input.front()->m_value = input1;
    m_input.back()->m_value = input2;
    return calculate();
}

int MyNeuronTest::test()
{
    MYLOG(LEVEL_DEBUG, "Skip neuron test");
    return 0;
    printf("myNeuronTest start\n");
    std::vector<int> input1 = {3, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> input2 = {2, 4, 5, 6, 7, 8, 9, 10, 1, 2};
    std::vector<int> output;
    for(int i = 0; i < 10; ++i)
    {
        output.push_back(input1[i] * input2[i]);
    }
    MyNeuron neu(2);
    for(int i = 0; i < 1; ++i)
    {
        neu.train(input1, input2, output);
    }
    for(int i = 0; i < 10; ++i)
    {
        printf("%d * %d = %d\n",input1[i], input2[i], neu.test(input1[i], input2[i]));
    }
    printf("myNeuronTest end\n");
    return 0;
}
