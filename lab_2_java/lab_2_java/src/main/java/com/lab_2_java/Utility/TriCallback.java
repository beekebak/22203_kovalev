package com.lab_2_java.Utility;

@FunctionalInterface
public interface TriCallback <R, T, U, V> {
    public R Apply(T t, U u, V v);
}
