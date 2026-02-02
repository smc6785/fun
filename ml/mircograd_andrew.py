
import math
import random
import numpy as np
import matplotlib.pyplot as plt

from graphviz import Digraph
def trace(root):
    nodes, edges = set(), set()
    def build(v):
        if v not in nodes:
            nodes.add(v)
            for child in v._prev:
                edges.add((child, v))
                build(child)
    build(root)
    return nodes, edges

def draw_dot(root):
    dot = Digraph(format='svg', graph_attr={'rankdir': 'LR'})

    nodes, edges = trace(root)
    for n in nodes:
        uid = str(id(n))
        dot.node(name=uid, label = "{%s | data %.4f | grad %.4f }" % (n.label, n.data, n.grad), shape='record')
        if n._op:
            dot.node(name=uid+n._op, label=n._op)
            dot.edge(uid+n._op,uid)

    for n1, n2 in edges:
        dot.edge(str(id(n1)), str(id(n2)) +n2._op)
    dot.render("smc", view=True, format='png')
    return dot

class Value:
    def __init__(self, data,_children=(), _op='', label=''):
        self.data = data
        # set() in python is ann unordered collection of unique elements.
        self._prev = set(_children)
        self._op = _op
        self.label = label
        self.grad = 0
        # lambda in python allows user to define an anonymous fucntions.
        self._backward = lambda: None

    def __repr__(self):
        return f"Value(data={self.data})"
    def __add__(self, other):
        other = other if isinstance(other, Value) else Value(other)
        out = Value(self.data+other.data, (self, other), '+')
        def _backward():
          self.grad += 1.0 * out.grad
          other.grad += 1.0 * out.grad
        out._backward = _backward
        return out
    def __mul__(self, other):
        other = other if isinstance(other, Value) else Value(other)
        out = Value(self.data*other.data, (self, other), '*')
        def _backward():
          self.grad += other.data * out.grad
          other.grad += self.data * out.grad
        out._backward = _backward
        return out
    def __rmul__(self, other):
        # when __mul__ fails, a fallback function
        return self*other
    def tanh(self):
        x = self.data
        t = (math.exp(2*x)-1)/(math.exp(2*x)+1)
        out = Value(t, (self, ), "tanh")
        def _backward():
          self.grad += (1 - t**2) * out.grad
        out._backward = _backward
        return out
    def exp(self):
        x = self.data
        out = Value(math.exp(x), (self, ), 'exp')
        def _backward():
          self.grad = out.data * out.grad
        out._backward = _backward
        return out
    def __truediv__(self, other):
        return self * other ** -1
    def __pow__(self, other):
        assert isinstance(other, (int, float)), "int or float"
        out = Value(self.data**other, (self,), f'**{other}')
        def _backward():
            self.grad += other * (self.data **(other-1)) * out.grad
        out._backward = _backward
        return out
    def __sub__(self, other):
        return self + (-other)
    def __neg__(self):
        return self*-1
    def backward(self):
        topo = []
        visited = set()
        def build_topo(v):
          if v not in visited:
            visited.add(v)
            for child in v._prev:
              build_topo(child)
            topo.append(v)
        build_topo(self)

        self.grad = 1.0
        for node in reversed(topo):
          node._backward()



'''
Chain rule:
dz/dx = (dz/dy * dy/dx)

A Neuron:
input and weights w0x0 w1x1 w2x2
cell boady: sum(wixi) + b
activation function: f
# One of the activation functions
plt.plot(np.arange(-5, 5, 1), np.tanh(np.arange(-5, 5, 1)))
plt.grid()
plt.show()
'''

# inputs x1, x2
x1 = Value(2.0, label='x1')
x2 = Value(-3.0, label='x2')
# weights w1, w2
w1 = Value(-3.0, label='w1')
w2 = Value(1.0, label='w2')
# bias of the neuron
b = Value(6.88, label='b')


x1w1 = x1*w1
x1w1.label = 'x1w1'
x2w2 = x2*w2
x2w2.label = 'x2w2'

n = x1w1+x2w2 +b
n.label='n'

# output o
o = n.tanh()
e = (2*n).exp()
o = (e-1)/(e+1)
# do/dn = 1 - tanh(x)**2
# (a.__mul__(b)).__add__(c)

o.grad = 1.0
o._backward()

n._backward()
b._backward()

o.backward()
# draw the result.
#draw_dot(o)

aa = Value(3.0, label='a')
bb = Value(3.0, label='b')
aa/bb

"""
import torch
x1 = torch.Tensor([2.0]).double()
x1.requires_grad = True
x2 = torch.Tensor([0.0]).double()
x2.requires_grad = True
w1 = torch.Tensor([-3.0]).double()
w2.requires_grad = True
w1 = torch.Tensor([1.0]).double()
w2.requires_grad = True
b = torch.Tensor([0.68813]).double()
b.requires_grad = True

n = x1*w1 + x2*w2 + b
o = torch.tanh(n)

print(o.data.item())
o.backward()

print("x2", x2.grad.item())
print("w2", w2.grad.item())
print("x1", x1.grad.item())
print("w1", w1.grad.item())

"""

class Neuron:
  def __init__(self, nin):
    self.w = [Value(random.uniform(-1,1)) for _ in range(nin)]
    self.b = Value(random.uniform(-1,1))
  def __call__(self, x):
    # n(x) = n.__call__(x)
    # w*x+b
    # zip() in python pairs up elements and creates a new iterator.
    # print(list(zip(self.w, x)))
    act = Value(0.0)
    for wi, xi in zip(self.w, x):
      act += xi*wi
    act += self.b
    out = act.tanh()
    return out
  def parameters(self):
    return self.w + [self.b]

x = [2.0, 3.0]
n = Neuron(2)
n(x)
# print(n(x))

class Layer:
  def __init__(self, nin, nout):
    self.neurons = [Neuron(nin) for _ in range (nout)]
  def __call__(self, x):
    outs = [n(x) for n in self.neurons]
    return outs[0] if len(outs) ==1 else outs
  def parameters(self):
    params = []
    for neuron in self.neurons:
      ps = neuron.parameters()
      params.extend(ps)
    return params


x = [2.0, 3.0]
n = Layer(2,3)
n(x)
# print(n(x))

class MLP:
  # multilayer perceptron
  def __init__(self, nin, nouts):
    sz = [nin] + nouts
    self.layers = [Layer(sz[i], sz[i+1]) for i in range(len(nouts))]
  def __call__(self, x):
    for layer in self.layers:
      x = layer(x)
    return x
  def parameters(self):
    params = []
    for p in self.layers:
      for neuron in p.neurons:
        ps = neuron.parameters()
        params.extend(ps)
    return params


x = [2.0, 3.0, -1.0]
n = MLP(3, [4, 4, 1])
n(x)
# print(n(x))
# draw_dot(n(x))

# Example dataset
xs = [
  [2.0, 3.0, -1.0],
  [3.0, -1.0, 0.5],
  [0.5, 1.0, 1.0],
  [1.0, 1.0, -1.0],
]

# desired targets
ys = [1.0, -1.0, -1.0, 1.0]

ypred = [n(x) for x in xs]
print(ypred)

# loss, single number calculates the performance of the neural net in deep learning.
# ygt, y ground truth.
# mean squre error loss.
loss = [(yout-ygt)**2 for ygt, yout in zip(ys, ypred)]
loss = sum(loss, Value(0.0))
print(loss)

loss.backward()
# draw_dot(loss)
# print(n.layers[0].neurons[0].w[0].grad)

print(len(n.parameters()))
print(n.parameters())

# lower loss after change the parameters.
# gradient desent report this process N times.
for i in range(20):
  # forward pass
  ypred = [n(x) for x in xs]
  loss = [(yout-ygt)**2 for ygt, yout in zip(ys, ypred)]
  loss = sum(loss, Value(0.0))

  # zero grad
  for p in n.parameters():
    p.grad = 0.0
  # backward pass
  loss.backward()

  # update with a fixed learning rate.
  for p in n.parameters():
    p.data += -0.08 * p.grad

  print(i, loss)

print(ypred)

