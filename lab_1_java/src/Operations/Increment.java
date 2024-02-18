package Operations;

//stands for "+"
class Increment implements Operation{
    public void Operate(byte[] data, int dataPointer){
        data[dataPointer]++;
    }
}
