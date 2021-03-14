#include <iostream>
#include <vector>

class IMarkable
{
public: 
	virtual void mark(int value, int index) = 0;
};

class ProxyVal 
{
private:
	int proxyVal_;
	int index_;
	IMarkable* objectToMark_;
  
public:
	ProxyVal(IMarkable* markable, int val, int index) 
		: objectToMark_(markable), proxyVal_(val), index_(index) {};

	void operator=(const int& value) {
		proxyVal_ = value;
		objectToMark_->mark(value, index_);
	}

	operator int() {
		return proxyVal_;
	}
	
};

class MarkableVector : IMarkable
{
private:
	struct MarkableValue
  {
		int val;
		bool isMarked;
		MarkableValue(int value, bool marked)
       : val(value), isMarked(marked) {}; 
	};

private:
	ProxyVal proxyVal_;
	std::vector<MarkableValue> data_;

public:
	MarkableVector() {};

	void add(int val)
	{
		data_.push_back(MarkableValue(val, (val%2 == 0)));
	}

	void mark(int value, int index) override
	{
		data_[index].val = value;
		data_[index].isMarked = (value % 2 == 0);
	}

	ProxyVal operator[](std::size_t index)
	{
		return ProxyVal(this, data_[index].val, index); 
	}
};




int main()
{
	std::cout << "start ... " << std::endl;

	MarkableVector vec;
	vec.add(1);
	vec.add(2);

	int v = vec[0];

	std::cout << "integer value at index 0: " << v << std::endl;

	auto c = vec[0];
	c = 10;

	std::cout << "the same integer after assignment to 10 is equal to " << vec[0] << std::endl;

}


