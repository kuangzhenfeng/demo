#include "neuron.h"
#include <stdio.h>
#include <math.h>
#include <algorithm>

static const double studySpeed = 0.1;   // 学习率

Neuron::Neuron(int inputNum, double value) : m_value(value)
{
    for(int i = 0; i < inputNum; ++i)
    {
        Neuron *neu = new Neuron();
        m_input.push_back(neu);
        neu->m_output.push_back(this);
    }
}

Neuron::~Neuron()
{

}

double Neuron::calculate()
{
    double res = m_value;
    std::list<Neuron *>::iterator ite;
    for(ite = m_input.begin(); ite != m_input.end(); ++ite)
    {
        res += (*ite)->calculate() * (*ite)->m_weight;
    }
    // return softmax(res);
    return res;
}

void Neuron::update(double target)
{
    double current = calculate();
    if(current == target)
    {
        printf("OK\n");
        return;
    }
    printf("calibrate, current=%.2lf target=%.2lf ", current, target);
    std::list<Neuron *>::iterator ite;
    for(ite = m_input.begin(); ite != m_input.end(); ++ite)
    {
        (*ite)->m_weight += studySpeed * (target - current);
        printf("weight=%lf ", (*ite)->m_weight);
        // (*ite)->update((*ite)->calculate() * (*ite)->m_weight);      // TODO: 修正前面分支
    }
    printf("\n");
}

double Neuron::softmax(double x)
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

void Neuron::train(std::vector<int> input1, std::vector<int> input2, std::vector<int> output)
{
    for(int i = 0; i < output.size(); ++i)
    {
        m_input.front()->m_value = input1[i];
        m_input.back()->m_value = input2[i];
        update(output[i]);
    }

}

int Neuron::test(int input1, int input2)
{
    m_input.front()->m_value = input1;
    m_input.back()->m_value = input2;
    return calculate();
}