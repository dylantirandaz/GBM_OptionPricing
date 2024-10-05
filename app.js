import React, { useState, useEffect } from 'react';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from 'recharts';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Input } from '@/components/ui/input';
import { Button } from '@/components/ui/button';
import { Tabs, TabsContent, TabsList, TabsTrigger } from '@/components/ui/tabs';
import { AlertCircle, RefreshCw } from 'lucide-react';

const generateMockData = (basePrice, numPoints) => {
  return Array.from({ length: numPoints }, (_, i) => ({
    time: i,
    price: basePrice + (Math.random() - 0.5) * 10,
    impliedVol: Math.max(0.1, Math.min(0.5, 0.2 + (Math.random() - 0.5) * 0.1)),
  }));
};

const AdvancedOptionPricingDashboard = () => {
  const [params, setParams] = useState({
    S0: 100,
    K: 100,
    r: 0.05,
    volatility: 0.2,
    T: 1,
    numSimulations: 100000
  });

  const [prices, setPrices] = useState({
    europeanCall: null,
    europeanPut: null,
    asian: null,
    marketData: []
  });

  const [isLoading, setIsLoading] = useState(false);

  useEffect(() => {
    // Simulate real-time data updates
    const interval = setInterval(() => {
      setPrices(prevPrices => ({
        ...prevPrices,
        marketData: generateMockData(params.S0, 100)
      }));
    }, 5000);

    return () => clearInterval(interval);
  }, [params.S0]);

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setParams(prevParams => ({
      ...prevParams,
      [name]: parseFloat(value)
    }));
  };

  const calculatePrices = () => {
    setIsLoading(true);
    // Simulate API call to backend
    setTimeout(() => {
      setPrices(prevPrices => ({
        ...prevPrices,
        europeanCall: (Math.random() * 10 + 5).toFixed(4),
        europeanPut: (Math.random() * 10 + 5).toFixed(4),
        asian: (Math.random() * 8 + 4).toFixed(4),
      }));
      setIsLoading(false);
    }, 1000);
  };

  return (
    <div className="container mx-auto p-4 bg-gray-100 min-h-screen">
      <h1 className="text-3xl font-bold mb-6">Advanced Option Pricing Dashboard</h1>
      
      <div className="grid grid-cols-1 md:grid-cols-3 gap-4 mb-6">
        <Card>
          <CardHeader>
            <CardTitle>Option Parameters</CardTitle>
          </CardHeader>
          <CardContent>
            <div className="grid grid-cols-2 gap-4">
              <Input type="number" name="S0" value={params.S0} onChange={handleInputChange} placeholder="S0" />
              <Input type="number" name="K" value={params.K} onChange={handleInputChange} placeholder="K" />
              <Input type="number" name="r" value={params.r} onChange={handleInputChange} placeholder="r" step="0.01" />
              <Input type="number" name="volatility" value={params.volatility} onChange={handleInputChange} placeholder="σ" step="0.01" />
              <Input type="number" name="T" value={params.T} onChange={handleInputChange} placeholder="T" step="0.1" />
              <Input type="number" name="numSimulations" value={params.numSimulations} onChange={handleInputChange} placeholder="Simulations" />
            </div>
            <Button className="mt-4 w-full" onClick={calculatePrices} disabled={isLoading}>
              {isLoading ? <RefreshCw className="mr-2 h-4 w-4 animate-spin" /> : 'Calculate Prices'}
            </Button>
          </CardContent>
        </Card>

        <Card>
          <CardHeader>
            <CardTitle>Option Prices</CardTitle>
          </CardHeader>
          <CardContent>
            <div className="space-y-2">
              <p><strong>European Call:</strong> ${prices.europeanCall || '—'}</p>
              <p><strong>European Put:</strong> ${prices.europeanPut || '—'}</p>
              <p><strong>Asian Option:</strong> ${prices.asian || '—'}</p>
            </div>
          </CardContent>
        </Card>

        <Card>
          <CardHeader>
            <CardTitle>Market Data</CardTitle>
          </CardHeader>
          <CardContent>
            <div className="space-y-2">
              <p><strong>Current Price:</strong> ${prices.marketData[prices.marketData.length - 1]?.price.toFixed(2) || '—'}</p>
              <p><strong>Implied Volatility:</strong> {(prices.marketData[prices.marketData.length - 1]?.impliedVol * 100).toFixed(2)}%</p>
            </div>
          </CardContent>
        </Card>
      </div>

      <Tabs defaultValue="price" className="w-full">
        <TabsList>
          <TabsTrigger value="price">Price Chart</TabsTrigger>
          <TabsTrigger value="volatility">Volatility Chart</TabsTrigger>
        </TabsList>
        <TabsContent value="price">
          <Card>
            <CardHeader>
              <CardTitle>Price Movement</CardTitle>
            </CardHeader>
            <CardContent>
              <ResponsiveContainer width="100%" height={400}>
                <LineChart data={prices.marketData}>
                  <CartesianGrid strokeDasharray="3 3" />
                  <XAxis dataKey="time" />
                  <YAxis />
                  <Tooltip />
                  <Legend />
                  <Line type="monotone" dataKey="price" stroke="#8884d8" dot={false} />
                </LineChart>
              </ResponsiveContainer>
            </CardContent>
          </Card>
        </TabsContent>
        <TabsContent value="volatility">
          <Card>
            <CardHeader>
              <CardTitle>Implied Volatility</CardTitle>
            </CardHeader>
            <CardContent>
              <ResponsiveContainer width="100%" height={400}>
                <LineChart data={prices.marketData}>
                  <CartesianGrid strokeDasharray="3 3" />
                  <XAxis dataKey="time" />
                  <YAxis />
                  <Tooltip />
                  <Legend />
                  <Line type="monotone" dataKey="impliedVol" stroke="#82ca9d" dot={false} />
                </LineChart>
              </ResponsiveContainer>
            </CardContent>
          </Card>
        </TabsContent>
      </Tabs>

      <div className="mt-4 flex items-center text-yellow-600">
        <AlertCircle className="mr-2" />
        <p>Note: This is a frontend demo with simulated data. In a production environment, it would connect to real-time market data and a sophisticated backend pricing engine.</p>
      </div>
    </div>
  );
};

export default AdvancedOptionPricingDashboard;
