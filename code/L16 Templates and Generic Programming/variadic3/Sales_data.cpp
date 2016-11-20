#include"Sales_data.h"

#include<functional>
using std::less;

namespace std{
	size_t std::hash<Sales_data>::operator()(const Sales_data &s)const
	{
		return hash<string>()(s.isbn()) ^
			hash<unsigned>()(s.units_sold) ^
			hash<double>()(s.revenue);
	}
}

Sales_data::Sales_data(istream &is)
{
	is >> *this;		//read a transaction from input into Sales_data
}

double Sales_data::avg_price()const
{
	if (units_sold)
		return revenue / units_sold;
	return 0;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}

ostream& operator<<(ostream &os, const Sales_data &s)
{
	os << "ISBN: " << s.isbn() << "\tunits_sold: "
		<< s.units_sold << "\trevenue: " << s.revenue;
	return os;
}

istream& operator>>(istream &is, Sales_data &s)
{
	double price;
	is >> s.bookNo >> s.units_sold >> price;
	if (is)
		s.revenue = s.units_sold * price;
	else
		s = Sales_data();
	return is;
}