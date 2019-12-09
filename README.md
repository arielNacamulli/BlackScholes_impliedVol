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

Data initialization and calibration of a volatility curve are shown in the following examples

### Import Data

Data of vanilla option prices are converted to spot implied volatilities. It can be done as follows

    // inserting some data
    Date settDate(06,12,2019), matDate(20,12,2019);
    VolSmile smile(matDate,settDate,F0,B);

    smile.newSpot(2000,1117.75);
    smile.newSpot(2475.00,0.10,-1);
    smile.newSpot(2800.00,1.10,-1);
    smile.newSpot(2850.00,1.50,-1);
    smile.newSpot(2900.00,2.8,-1);
    smile.newSpot(3150.00,20.50);
    smile.newSpot(3075.00,19.67,-1);
    smile.newSpot(3200.00,2.32);
    
    // printing spot volatilities
    smile.print();
    
Those lines print the following:

    0: Strike 2000   Volatility 0.960643
    1: Strike 2475   Volatility 0.399852
    2: Strike 2800   Volatility 0.265801
    3: Strike 2850   Volatility 0.239617
    4: Strike 2900   Volatility 0.225121
    5: Strike 3075   Volatility 0.153409
    6: Strike 3150   Volatility 0.140418
    7: Strike 3200   Volatility 0.0970397

Or, in a more reusable way

    Date settDate(06,12,2019), matDate(20,12,2019);
    VolSmile smile(matDate,settDate,F0,B);

    smile.read("prices.txt");
    
Given that the prices are written as 

    2000 1117.75 1
    2475.00 0.10 -1
    2800.00 1.10 -1
    2850.00 1.50 -1
    2900.00 2.8 -1
    3150.00 20.50 1
    3075.00 19.67 -1
    3200.00 2.32 1
    
### Calibration

Now, spline interpolation is used to calibrate the curve

    smile.calibrate();
    
And now the curve can be used to get the volatility for a given strike and price

    double Kbar = 3100;
    double sig = smile.interpolate(Kbar);
    double TT = yearfrac(settDate,matDate,ACT365);

    double price = blkprice(F0,B,Kbar,TT,sig,1); // mkt price 46.00
    
Which returns a value close to the market one:

    >> 45.9908

## Plot

One can plot volatility curve using `plotter.py` calling

    smile.write("curve.txt");
    
And then running the plotting script.

In the example we obtain the following

![alt](https://github.com/arielNacamulli/BlackScholes_impliedVol/edit/master/plot.png)
## Authors

* **Ariel Nacamulli** - [arielNacamulli](https://github.com/arielNacamulli)

## Acknowledgments

* Part of the code used was seen during the classes of Algorithms and Parallel Computing by Professor Ardagna at Politecnico di Milano
