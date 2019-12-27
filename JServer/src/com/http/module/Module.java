package com.http.module;

/*
 * The user must implement this class in order to create relation between a class and the database entry.
 * The database holds the value of all attributes of the class
 * The toString method must be implemented as to have valid insertion
 */
public class Module<T> {
    private Class<T> clazz;

    public Module(Class<T> clazz) {
        this.clazz = clazz;
    }
}
