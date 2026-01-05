from tinygrad.tensor import Tensor

x = Tensor.arange(1,10).reshape((3, 3))
y = Tensor.arange(10,19).reshape((3, 3))

product = x.matmul(y)
product_sum = product.sum()
print(product_sum.numpy())
