package com.example.to_do_list.Todo;


import java.time.LocalDate;
import java.time.Period;

import org.springframework.cglib.core.Local;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.SequenceGenerator;
import jakarta.persistence.Table;


@Entity
@Table
public class Todo {
    @Id
    @SequenceGenerator(
        name = "todo_sequence",
        sequenceName = "todo_sequence",
        allocationSize = 1
    )
    @GeneratedValue(
        strategy = GenerationType.SEQUENCE,
        generator = "todo_sequence"
    )
    private Long id;

    private String todoAction;
    private Boolean isCompleted;

    public Todo() {};

    public Todo(String todo_action, Boolean is_completed) {
        this.todoAction = todo_action;
        this.isCompleted = is_completed;
    }

    public Long getId() {
        return this.id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getTodoAction() {
        return this.todoAction;
    }

    public void setTodoAction(String todo_action) {
        this.todoAction = todo_action;
    }

    public Boolean getIsCompleted() {
        return this.isCompleted;
    }

    public void setIsCompleted(Boolean is_completed){
        this.isCompleted = is_completed;
    }

}
