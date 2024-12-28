package com.example.to_do_list.Todo;

import java.time.LocalDate;
import java.util.List;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.example.to_do_list.Student.Student;

@RestController
public class TodoController {

    @GetMapping("/")
    public String hello() {
        return "Hello";
    }

}