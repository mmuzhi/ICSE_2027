import math
import struct

class ComplexCalculator:
    class ComplexNumber:
        def __init__(self, real, imaginary):
            self._real = real
            self._imaginary = imaginary
        
        def getReal(self):
            return self._real
        
        def getImaginary(self):
            return self._imaginary
        
        def __eq__(self, obj):
            if not isinstance(obj, ComplexCalculator.ComplexNumber):
                return False
            that = obj
            
            def double_to_bits(d):
                if math.isnan(d):
                    return 0x7FF8000000000000
                s = struct.pack('>d', d)
                bits = struct.unpack('>Q', s)[0]
                return bits
            
            return (double_to_bits(self._real) == double_to_bits(that._real) and 
                    double_to_bits(self._imaginary) == double_to_bits(that._imaginary))
        
        def __str__(self):
            s = str(self._real)
            if self._imaginary >= 0:
                s += '+' + str(self._imaginary) + 'j'
            else:
                s += str(self._imaginary) + 'j'
            return s
    
    def add(self, c1, c2):
        real = c1.getReal() + c2.getReal()
        imaginary = c1.getImaginary() + c2.getImaginary()
        return ComplexCalculator.ComplexNumber(real, imaginary)
    
    def subtract(self, c1, c2):
        real = c1.getReal() - c2.getReal()
        imaginary = c1.getImaginary() - c2.getImaginary()
        return ComplexCalculator.ComplexNumber(real, imaginary)
    
    def multiply(self, c1, c2):
        real = c1.getReal() * c2.getReal() - c1.getImaginary() * c2.getImaginary()
        imaginary = c1.getReal() * c2.getImaginary() + c1.getImaginary() * c2.getReal()
        return ComplexCalculator.ComplexNumber(real, imaginary)
    
    def divide(self, c1, c2):
        denominator = c2.getReal() * c2.getReal() + c2.getImaginary() * c2.getImaginary()
        real = (c1.getReal() * c2.getReal() + c1.getImaginary() * c2.getImaginary()) / denominator
        imaginary = (c1.getImaginary() * c2.getReal() - c1.getReal() * c2.getImaginary()) / denominator
        return ComplexCalculator.ComplexNumber(real, imaginary)