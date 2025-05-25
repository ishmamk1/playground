import { useState, useEffect } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'
import axios from 'axios'
import AddTodo from './components/addTodo'
import GetTodos from './components/getTodos'

interface hello {
  message: string;
};

function App() {
  const [count, setCount] = useState(0);
  const [hello, setHello] = useState<hello>();
  const [error, setError] = useState<string>('');

  useEffect(() => {
    const hello = async () => {
      try {
        const response = await axios.get<hello>('http://127.0.0.1:3000/hello');
        console.log(response.data);
        setHello(response.data);
      } catch (err) {
        console.log(err)
        setError("Failed to fetch todo.");
      }
    };

    hello();
  }, []);


  return (
    <>
      {error && <p style={{ color: 'red' }}>{error}</p>}
      {hello && <p>{hello.message}</p>}
      {!hello && !error && <p>No data found.</p>}
      <AddTodo/>
      <GetTodos/>
    </>
  )
}

export default App;


