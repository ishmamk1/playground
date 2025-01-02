package com.example.to_do_list.Todo;

import java.time.LocalDate;
import java.util.List;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PatchMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(path = "api/v1/todo")
@CrossOrigin(origins = "http://localhost:5173")
public class TodoController {

    private final TodoService todoService;

    @Autowired TodoController(TodoService todoService) {
        this.todoService = todoService;
    }

    @GetMapping("/")
    public String example() {
        return "CORS enabled!";
    }

    @GetMapping
    public List<Todo> getTodoActions() {
        return todoService.getAllTodo();
    }

    @PostMapping
    public void addTodoAction(@RequestBody Todo todo) {
        todoService.addTodoAction(todo);
    }

    @DeleteMapping("/{id}")
    public void deleteTodo(@PathVariable("id") Long id) {
        todoService.deleteById(id); 
    }

    @PutMapping("/{id}")
    public void updateTodo(@PathVariable("id") Long id, @RequestBody String updateTodo) {
        todoService.updateTodoAction(id, updateTodo);
    }

}