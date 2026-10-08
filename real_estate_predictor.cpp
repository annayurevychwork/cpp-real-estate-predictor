/*
We have cost constant for 1 square meter of area, for one bedroom or bathroom, for distance from the subway, for commercial property.
Forecast calculation: sum of real price, calculated by multiplying data from the realtor by cost constant, and the average error modulo.
Error: the difference between the real property price, specified by the realtor, and the real price, calculated by the cost constant.
Result: maximum property price.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

const double ONE_SQUARE_METER = 62000;
const double BEDROOM_PRICE = 50000;
const double BATHROOM_PRICE = 25000;
const double UNDERGROUND_DISTANCE_DEPENDENCE = -500; //the farther from the subway, the cheaper
const double MARKUP_COMMERCIAL = 10000;

const int MAX_AREA = 200;
const int MIN_AREA = 10;

const int MAX_BEDROOMS = 4;
const int MIN_BEDROOMS = 1;

const int MAX_BATHROOMS = 3;
const int MIN_BATHROOMS = 1;

const int MAX_MINUTES_TO_UNDERGROUND = 90;
const int MIN_MINUTES_TO_UNDERGROUND = 1;

const int MAX_PRICE = 13000000;
const int MIN_PRICE = 600000;

struct Realtor_property
{
    double area;
    int bedrooms;
    int bathrooms;
    int time_to_underground;
    bool commercial_or_residential;
    double price;
};

struct Your_property
{
    double area;
    int bedrooms;
    int bathrooms;
    int time_to_underground;
    bool commercial_or_residential;
};

bool is_area_ok (double area)
{
    if (area > MAX_AREA || area < MIN_AREA)
    {
        cout << "Seems like area is incorrect. Please enter area again (from " << MIN_AREA << " to " << MAX_AREA << "): ";
        return false;
    }
    return true;
}

bool is_number_of_bedrooms_ok (int bedrooms)
{
    if (bedrooms > MAX_BEDROOMS || bedrooms < MIN_BEDROOMS)
    {
        cout << "Seems like number of bedrooms is incorrect. Please enter number of bedrooms again (from " << MIN_BEDROOMS
        << " to " << MAX_BEDROOMS << "): ";
        return false;
    }
    return true;
}

bool is_number_of_bathrooms_ok (int bathrooms)
{
    if (bathrooms > MAX_BATHROOMS || bathrooms < MIN_BATHROOMS)
    {
        cout << "Seems like number of bathrooms is incorrect. Please enter number of bathrooms again (from " << MIN_BATHROOMS
        << " to " << MAX_BATHROOMS << "): ";
        return false;
    }
    return true;
}

bool is_time_to_underground_ok (int time_to_underground)
{
    if (time_to_underground > MAX_MINUTES_TO_UNDERGROUND || time_to_underground < MIN_MINUTES_TO_UNDERGROUND)
    {
        cout << "Seems like time to underground is incorrect. Please enter time to underground again (from "
        << MIN_MINUTES_TO_UNDERGROUND << " to " << MAX_MINUTES_TO_UNDERGROUND << "): ";
        return false;
    }
    return true;
}

bool is_price_ok (double price)
{
    if (price > MAX_PRICE || price < MIN_PRICE)
    {
        cout << "Seems like price is incorrect. Please enter price again (from " << MIN_PRICE << " to " << MAX_PRICE << "): ";
        return false;
    }
    return true;
}


double predict (vector <Realtor_property> &realtor_properties, vector <Your_property> &your_property)
{
    double average_error = 0; //відхилення
    double sum_errors = 0;
    double target = 0;

    for (int i = 0; i < realtor_properties.size(); i++)
    {
        if (realtor_properties[i].area == your_property[0].area &&
            realtor_properties[i].bedrooms == your_property[0].bedrooms &&
            realtor_properties[i].bathrooms == your_property[0].bathrooms &&
            realtor_properties[i].time_to_underground == your_property[0].time_to_underground &&
            realtor_properties[i].commercial_or_residential == your_property[0].commercial_or_residential)
        {
            cout << "MAX PRICE OF YOUR PROPERTY IS: ";
            return realtor_properties[i].price;
        }
    }

    for (int i = 0; i < realtor_properties.size(); i++)
    {
        sum_errors += realtor_properties[i].price - (realtor_properties[i].area * ONE_SQUARE_METER
        + realtor_properties[i].bedrooms * BEDROOM_PRICE + realtor_properties[i].bathrooms * BATHROOM_PRICE
        + realtor_properties[i].time_to_underground * UNDERGROUND_DISTANCE_DEPENDENCE
        + (int)realtor_properties[i].commercial_or_residential * MARKUP_COMMERCIAL);
    }

    average_error = sum_errors / realtor_properties.size();

    target = your_property[0].area * ONE_SQUARE_METER + your_property[0].bedrooms * BEDROOM_PRICE
    + your_property[0].bathrooms * BATHROOM_PRICE + your_property[0].time_to_underground * UNDERGROUND_DISTANCE_DEPENDENCE
    + (int)your_property[0].commercial_or_residential * MARKUP_COMMERCIAL + fabs(average_error);

    cout << "MAX PRICE OF YOUR PROPERTY IS: ";
    return target;
}

int main()
{
    vector <Realtor_property> realtor_properties;
    vector <Your_property> your_property;

    cout << "Imagine that you are a realtor. Enter features to create a property list." << endl << endl;

    double area;
    int bedrooms;
    int bathrooms;
    int time_to_underground;
    bool commercial_or_residential;
    double price;

    while (true)
    {
        cout << "PROPERTY #" << realtor_properties.size() + 1 << endl;

        cout << "Please enter area in square meters (from " << MIN_AREA << " to " << MAX_AREA << "). To stop entering properties, ";
        cout << "enter an area of 0: ";
        if (cin >> area)
        {
            if (area == 0)
            {
                if (realtor_properties.empty())
                {
                    cout << "No data to predict price" << endl;
                    return 0;
                }
                else
                {
                    break;
                }
            }
            while (!is_area_ok(area))
            {
                cin >> area;
            }
        }
        else
        {
            cout << "Unsupported data";
            return 0;
        }

        cout << "Please enter number of bedrooms (from " << MIN_BEDROOMS << " to " << MAX_BEDROOMS << "): ";
        if (cin >> bedrooms)
        {
            while (!is_number_of_bedrooms_ok(bedrooms))
            {
                cin >> bedrooms;
            }
        }
        else
        {
            cout << "Unsupported data";
            return 0;
        }

        cout << "Please enter number of bathrooms (from " << MIN_BATHROOMS << " to " << MAX_BATHROOMS << "): ";
        if (cin >> bathrooms)
        {
            while (!is_number_of_bathrooms_ok(bathrooms))
            {
                cin >> bathrooms;
            }
        }
        else
        {
            cout << "Unsupported data";
            return 0;
        }

        cout << "Please enter distance to underground in minutes (from " << MIN_MINUTES_TO_UNDERGROUND << " to "
        << MAX_MINUTES_TO_UNDERGROUND << "): ";
        if (cin >> time_to_underground)
        {
            while (!is_time_to_underground_ok(time_to_underground))
            {
                cin >> time_to_underground;
            }
        }
        else
        {
            cout << "Unsupported data";
            return 0;
        }

        cout << "Please enter whether this property is commercial ('1') or residential ('0'): ";
        if (!(cin >> commercial_or_residential))
        {
            cout << "Unsupported data";
            return 0;
        }

        cout << "Please enter price in UAH (from " << MIN_PRICE << " to " << MAX_PRICE << "): ";
        if (cin >> price)
        {
            while (!is_price_ok(price))
            {
                cin >> price;
            }
        }
        else
        {
            cout << "Unsupported data";
            return 0;
        }

        Realtor_property property;
        property.area = area;
        property.bedrooms = bedrooms;
        property.bathrooms = bathrooms;
        property.time_to_underground = time_to_underground;
        property.commercial_or_residential = commercial_or_residential;
        property.price = price;

        realtor_properties.push_back(property);

        cout << endl;
        cout << "-----------------------------------------------------------------------------------------------" << endl << endl;
    }

    cout << endl << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;

    cout << endl << "Property list entry finished." << endl;
    cout << "Now imagine that you are a customer. Enter features to find out the price of your property." << endl << endl;

    cout << "Please enter area in square meters (from " << MIN_AREA << " to " << MAX_AREA << "): ";
    if (cin >> area)
    {
        while (!is_area_ok(area))
        {
            cin >> area;
        }
    }
    else
    {
        cout << "Unsupported data";
        return 0;
    }

    cout << "Please enter number of bedrooms (from " << MIN_BEDROOMS << " to " << MAX_BEDROOMS << "): ";
    if (cin >> bedrooms)
    {
        while (!is_number_of_bedrooms_ok(bedrooms))
        {
            cin >> bedrooms;
        }
    }
    else
    {
        cout << "Unsupported data";
        return 0;
    }

    cout << "Please enter number of bathrooms (from " << MIN_BATHROOMS << " to " << MAX_BATHROOMS << "): ";
    if (cin >> bathrooms)
    {
        while (!is_number_of_bathrooms_ok(bathrooms))
        {
            cin >> bathrooms;
        }
    }
    else
    {
        cout << "Unsupported data";
        return 0;
    }

    cout << "Please enter distance to underground in minutes (from " << MIN_MINUTES_TO_UNDERGROUND << " to "
    << MAX_MINUTES_TO_UNDERGROUND << "): ";
    if (cin >> time_to_underground)
    {
        while (!is_time_to_underground_ok(time_to_underground))
        {
            cin >> time_to_underground;
        }
    }
    else
    {
        cout << "Unsupported data";
        return 0;
    }

    cout << "Please enter whether this apartment is commercial ('1') or residential ('0'): ";
    if (!(cin >> commercial_or_residential))
    {
        cout << "Unsupported data";
        return 0;
    }

    Your_property yours;
    yours.area = area;
    yours.bedrooms = bedrooms;
    yours.bathrooms = bathrooms;
    yours.time_to_underground = time_to_underground;
    yours.commercial_or_residential = commercial_or_residential;

    your_property.push_back(yours);

    cout << endl << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;

    cout << left;
    cout << fixed;
    cout.precision(2);
    cout << endl << setw(20) << "NUMBER OF PROPERTY" << setw(10) << "AREA" << setw(10) << "BEDROOMS" << setw(12) << "BATHROOMS"
    << setw(24) << "UNDERGROUND DISTANCE" << setw(20) << "COM(1) OR RES(0)" << setw(15) << "PRICE" << endl;
    for (int i = 0; i < realtor_properties.size(); i++)
    {
        cout << setw(20) << i + 1 << setw(10) << realtor_properties[i].area << setw(10) << realtor_properties[i].bedrooms
        << setw(12) << realtor_properties[i].bathrooms << setw(24) << realtor_properties[i].time_to_underground << setw(20)
        << (int)realtor_properties[i].commercial_or_residential << setw(15) << realtor_properties[i].price << endl;
    }
    cout << setw(20) << "Yours" << setw(10) << your_property[0].area << setw(10) << your_property[0].bedrooms << setw(12)
    << your_property[0].bathrooms << setw(24) << your_property[0].time_to_underground << setw(20)
    << (int)your_property[0].commercial_or_residential << endl;
        cout << endl << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;


    cout << endl << predict(realtor_properties, your_property);

    return 0;

}
