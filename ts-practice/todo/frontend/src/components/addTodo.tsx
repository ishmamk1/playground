import React, { useState } from 'react';

const AddTodo: React.FC = () => {
  const [todo, setTodo] = useState('');
  const [message, setMessage] = useState('');

  const handleSubmit = async () => {
    try {
        const response = await fetch('http://127.0.0.1:3000/add_todo', {
            method: 'POST',
            body: JSON.stringify({ item: todo }),
          });

      const data = await response.json();

      if (response.ok) {
        setMessage(`✅ ${data.message}`);
        setTodo('');
      } else {
        setMessage(`❌ Error: ${data.error || data.message || 'Unknown error'}`);
      }
    } catch (error) {
      console.error(error);
      setMessage('❌ Failed to send request to server.');
    }
  };

  return (
    <div style={{ padding: '1rem' }}>
      <h2>Add Todo</h2>
      <input
        type="text"
        value={todo}
        onChange={(e) => setTodo(e.target.value)}
        placeholder="Enter your todo"
        style={{ padding: '0.5rem', marginRight: '0.5rem' }}
      />
      <button onClick={handleSubmit} style={{ padding: '0.5rem 1rem' }}>
        Add
      </button>
      {message && <p style={{ marginTop: '1rem' }}>{message}</p>}
    </div>
  );
};

export default AddTodo;

