import React, { useEffect, useState } from 'react'
import axios from "axios";

import './App.css'
import InputField from './components/InputField';
import { Todo } from './components/Model';

import TodoList from './components/TodoList';

const App:React.FC = () =>  {

  const [todo, setTodo] = useState<string>("");
  const [todos, setTodos] = useState<Todo[]>([]);
  
  const fetchTodos = async () => {
    try {
      const response = await axios.get('/api/v1/todo'); 
      console.log(response.data);
      setTodos(response.data);
      return response.data;
    } catch (err) {
      console.error("Error fetching todos:", err);
    }
  };

  const handleAdd = async (e:React.FormEvent) => {
    e.preventDefault();
    try {
      const response = await axios.post('/api/v1/todo', {
        todoAction: todo,
        isCompleted: false,
      });
      console.log("Response: " + response.data);
      setTodo(""); 
      fetchTodos();
    } catch (error){
      console.error("Todo not added: ", error)
    }
  }

  const deleteTodo = async (id: number) => {
    try {
      await axios.delete(`/api/v1/todo/${id}`); // Send DELETE request to the backend
      fetchTodos(); // Update the state
    } catch (error) {
      console.error("Error deleting todo:", error);
    }
  };

  const toggleEdit = async () => {
    
  };
  


  
  useEffect(() => {
    fetchTodos();
  }, []);

  return (
    <>
      <div>
        <span className="heading">To-Do List</span>
        <InputField todo={todo} setTodo ={setTodo} handleAdd={handleAdd}/>
        <button onClick={fetchTodos}>Fetch Todos</button> {/* Button to fetch on demand */}
        <TodoList todos={todos} deleteTodo={deleteTodo}></TodoList>
      </div>
    </>
  )
}

export default App
