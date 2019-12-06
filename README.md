# Implied Volatility in Black & Scholes
I developed this library as a basic tool to start working on Quantitative Finance tasks.

The final instrument implemented is calibration of volatility smile (with Spline interpolation) but the library also includes Black/Black&Scholes formulae and implied volatility (spot).

The following examples are to show how to use the different functions.

## Standard Black

Let's test here basic Black's formula and relative implied volatility

    double F0 = 3118.50, B = 0.999, K = 3000.0, sigma = 0.3, T = 1;
    int flag = 1; // 1 for call, -1 for put

    double priceTest = blkprice(F0,B,K,T,sigma,flag);
    double sigmaTest = impvol(F0,B,K,T,priceTest,flag);


Printing the result we get

    std::cout << sigmaTest << std::endl;
    
    >> 0.3
    
As expected the function replicates the exact sigma.

## Volatility Smile

Calibration of a whole volatility curve is shown in the following example


    // inserting some data
    VolSmile smile(Date(20,03,2020),Date(20,11,2019),F0,B);
    smile.newSpot(2000,1120.14);
    smile.newSpot(2425.00,0.25,-1);
    smile.newSpot(2800.00,2.97,-1);
    smile.newSpot(2850.00,3.95,-1);
    smile.newSpot(3125.00,40.40,-1);
    smile.newSpot(3200.00,6.00);
    smile.newSpot(3100.00,50.00);
    
    // printing spot volatilities
    smile.print();
    
Those lines print the following:

    1: Strike 2425   Volatility 0.160477
    2: Strike 2800   Volatility 0.107137
    3: Strike 2850   Volatility 0.0980256
    4: Strike 3100   Volatility 0.0561828
    5: Strike 3125   Volatility 0.0517409
    6: Strike 3200   Volatility 0.0429889

Then spline interpolation is used to get the curve

    smile.calibrate();
    
And now the curve can be used to get the volatility for a given strike and price

    double Kbar = 3150;
    double sig = smile.interpolate(Kbar);
    double TT = yearfrac(Date(20,11,2019),Date(20,03,2020),ACT365);

    double price = blkprice(F0,B,Kbar,TT,sig,1);

Which returns a value close to the market one.

## Authors

* **Ariel Nacamulli** - [arielNacamulli](https://github.com/arielNacamulli)

## Acknowledgments

* Part of the code used was seen during the classes of Algorithms and Parallel Computing by Professor Ardagna at Politecnico di Milano
