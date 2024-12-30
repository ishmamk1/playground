package com.example.to_do_list.Student;

import java.text.DateFormat;
import java.time.LocalDate;
import java.util.List;

import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class StudentConfig {
    
    @Bean
    CommandLineRunner commandLineRunner(StudentRepository repository) {
        return args -> {
            Student ishmam = new Student(
                "Ishmam",
                LocalDate.now(),
                "ishmam@gmail.com"
            );
            Student abc = new Student(
                "ABC",
                LocalDate.now(),
                "ishmam@gmail.com"
            );
            
            repository.saveAll(
                List.of(ishmam, abc)
            );
        };
    }
}
