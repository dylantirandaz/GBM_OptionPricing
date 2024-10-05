import React, { useState, useEffect, useCallback } from 'react';
import { LineChart, Line, BarChart, Bar, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer, AreaChart, Area } from 'recharts';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Input } from '@/components/ui/input';
import { Button } from '@/components/ui/button';
import { Tabs, TabsContent, TabsList, TabsTrigger } from '@/components/ui/tabs';
import { Slider } from '@/components/ui/slider';
import { AlertCircle, RefreshCw, TrendingUp, TrendingDown, DollarSign, Percent } from 'lucide-react';

const formatTime = (date) => {
  return date.toTimeString().split(' ')[0];
};

const generateMockData = (basePrice, numPoints) => {
  return Array.from({ length: numPoints }, (_, i) => {
    const date = new Date();
    date.setMinutes(date.getMinutes() - (numPoints - i));
    return {
      time: formatTime(date),
      price: basePrice + (Math.random() - 0.5) * 10,
      volume: Math.floor(Math.random() * 10000),
      impliedVol: Math.max(0.1, Math.min(0.5, 0.2 + (Math.random() - 0.5) * 0.1)),
    };
  });
};

const calculateGreeks = (S, K, r, T, sigma) => {
  const d1 = (Math.log(S / K) + (r + sigma ** 2 / 2) * T) / (sigma * Math.sqrt(T));
  const d2 = d1 - sigma * Math.sqrt(T);
  const delta = Math.exp(-r * T) * (Math.random() * 0.5 + 0.5);
  const gamma = Math.exp(-r * T) * (Math.random() * 0.1 + 0.1);
  const theta = -Math.exp(-r * T) * (Math.random() * 5 + 1);
  const vega = Math.exp(-r * T) * (Math.random() * 10 + 5);
  return { delta, gamma, theta, vega };
};

const ProfessionalTradingDashboard = () => {
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

  const [greeks, setGreeks] = useState({
    delta: null,
    gamma: null,
    theta: null,
    vega: null
  });

  const [isLoading, setIsLoading] = useState(false);

  const updateMarketData = useCallback(() => {
    setPrices(prevPrices => ({
      ...prevPrices,
      marketData: generateMockData(params.S0, 100)
    }));
  }, [params.S0]);

  useEffect(() => {
    updateMarketData();
    const interval = setInterval(updateMarketData, 5000);
    return () => clearInterval(interval);
  }, [updateMarketData]);

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setParams(prevParams => ({
      ...prevParams,
      [name]: parseFloat(value)
    }));
  };

  const calculatePrices = () => {
    setIsLoading(true);
    setTimeout(() => {
      setPrices(prevPrices => ({
        ...prevPrices,
        europeanCall: (Math.random() * 10 + 5).toFixed(4),
        europeanPut: (Math.random() * 10 + 5).toFixed(4),
        asian: (Math.random() * 8 + 4).toFixed(4),
      }));
      setGreeks(calculateGreeks(params.S0, params.K, params.r, params.T, params.volatility));
      setIsLoading(false);
    }, 1000);
  };

  return (
    <div className="container mx-auto p-4 bg-gray-100 min-h-screen">
      <h1 className="text-3xl font-bold mb-6">Professional Trading Dashboard</h1>
      
      <div className="grid grid-cols-1 md:grid-cols-3 gap-4 mb-6">
        <Card>
          <CardHeader>
            <CardTitle>Option Parameters</CardTitle>
          </CardHeader>
          <CardContent>
            <div className="space-y-4">
              <div>
                <label className="block text-sm font-medium text-gray-700">Stock Price (S0)</label>
                <Input type="number" name="S0" value={params.S0} onChange={handleInputChange} className="mt-1" />
              </div>
              <div>
                <label className="block text-sm font-medium text-gray-700">Strike Price (K)</label>
                <Input type="number" name="K" value={params.K} onChange={handleInputChange} className="mt-1" />
              </div>
              <div>
                <label className="block text-sm font-medium text-gray-700">Risk-free Rate (r)</label>
                <Slider
                  name="r"
                  value={[params.r]}
                  onValueChange={([value]) => handleInputChange({ target: { name: 'r', value } })}
                  min={0}
                  max={0.1}
                  step={0.001}
                  className="mt-1"
                />
                <span className="text-sm text-gray-500">{(params.r * 100).toFixed(2)}%</span>
              </div>
              <div>
                <label className="block text-sm font-medium text-gray-700">Volatility (σ)</label>
                <Slider
                  name="volatility"
                  value={[params.volatility]}
                  onValueChange={([value]) => handleInputChange({ target: { name: 'volatility', value } })}
                  min={0}
                  max={1}
                  step={0.01}
                  className="mt-1"
                />
                <span className="text-sm text-gray-500">{(params.volatility * 100).toFixed(2)}%</span>
              </div>
              <div>
                <label className="block text-sm font-medium text-gray-700">Time to Expiration (T)</label>
                <Input type="number" name="T" value={params.T} onChange={handleInputChange} className="mt-1" step="0.1" />
              </div>
              <div>
                <label className="block text-sm font-medium text-gray-700">Number of Simulations</label>
                <Input type="number" name="numSimulations" value={params.numSimulations} onChange={handleInputChange} className="mt-1" />
              </div>
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
            <div className="space-y-4">
              <div className="flex items-center justify-between">
                <span className="text-sm font-medium">European Call:</span>
                <span className="text-lg font-bold text-green-600">${prices.europeanCall || '—'}</span>
              </div>
              <div className="flex items-center justify-between">
                <span className="text-sm font-medium">European Put:</span>
                <span className="text-lg font-bold text-red-600">${prices.europeanPut || '—'}</span>
              </div>
              <div className="flex items-center justify-between">
                <span className="text-sm font-medium">Asian Option:</span>
                <span className="text-lg font-bold text-blue-600">${prices.asian || '—'}</span>
              </div>
            </div>
          </CardContent>
        </Card>

        <Card>
          <CardHeader>
            <CardTitle>Greeks</CardTitle>
          </CardHeader>
          <CardContent>
            <div className="space-y-4">
              <div className="flex items-center justify-between">
                <span className="text-sm font-medium">Delta (Δ):</span>
                <span className="text-lg font-bold">{greeks.delta?.toFixed(4) || '—'}</span>
              </div>
              <div className="flex items-center justify-between">
                <span className="text-sm font-medium">Gamma (Γ):</span>
                <span className="text-lg font-bold">{greeks.gamma?.toFixed(4) || '—'}</span>
              </div>
              <div className="flex items-center justify-between">
                <span className="text-sm font-medium">Theta (Θ):</span>
                <span className="text-lg font-bold">{greeks.theta?.toFixed(4) || '—'}</span>
              </div>
              <div className="flex items-center justify-between">
                <span className="text-sm font-medium">Vega (ν):</span>
                <span className="text-lg font-bold">{greeks.vega?.toFixed(4) || '—'}</span>
              </div>
            </div>
          </CardContent>
        </Card>
      </div>

      <Tabs defaultValue="price" className="w-full">
        <TabsList className="grid w-full grid-cols-4">
          <TabsTrigger value="price">Price Chart</TabsTrigger>
          <TabsTrigger value="volume">Volume Chart</TabsTrigger>
          <TabsTrigger value="volatility">Volatility Surface</TabsTrigger>
          <TabsTrigger value="pnl">P&amp;L Analysis</TabsTrigger>
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
        <TabsContent value="volume">
          <Card>
            <CardHeader>
              <CardTitle>Trading Volume</CardTitle>
            </CardHeader>
            <CardContent>
              <ResponsiveContainer width="100%" height={400}>
                <BarChart data={prices.marketData}>
                  <CartesianGrid strokeDasharray="3 3" />
                  <XAxis dataKey="time" />
                  <YAxis />
                  <Tooltip />
                  <Legend />
                  <Bar dataKey="volume" fill="#82ca9d" />
                </BarChart>
              </ResponsiveContainer>
            </CardContent>
          </Card>
        </TabsContent>
        <TabsContent value="volatility">
          <Card>
            <CardHeader>
              <CardTitle>Implied Volatility Surface</CardTitle>
            </CardHeader>
            <CardContent>
              <ResponsiveContainer width="100%" height={400}>
                <AreaChart data={prices.marketData}>
                  <CartesianGrid strokeDasharray="3 3" />
                  <XAxis dataKey="time" />
                  <YAxis />
                  <Tooltip />
                  <Legend />
                  <Area type="monotone" dataKey="impliedVol" stroke="#8884d8" fill="#8884d8" />
                </AreaChart>
              </ResponsiveContainer>
            </CardContent>
          </Card>
        </TabsContent>
        <TabsContent value="pnl">
          <Card>
            <CardHeader>
              <CardTitle>Profit &amp; Loss Analysis</CardTitle>
            </CardHeader>
            <CardContent>
              <div className="text-center text-gray-500">
                P&amp;L analysis chart would be implemented here, showing potential profits and losses across different price scenarios.
              </div>
            </CardContent>
          </Card>
        </TabsContent>
      </Tabs>

      <div className="mt-4 flex items-center text-yellow-600">
        <AlertCircle className="mr-2" />
        <p>Note: This is an advanced frontend demo with simulated data. In a production environment, it would connect to real-time market data and a sophisticated backend pricing engine.</p>
      </div>
    </div>
  );
};

export default ProfessionalTradingDashboard;
