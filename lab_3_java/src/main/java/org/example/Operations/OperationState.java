package org.example.Operations;

public enum OperationState {
    INITIALIZED_CONNECTION,
    REQUESTED_CHECK,
    ANSWERED_CHECK_YES,
    ANSWERED_CHECK_NO,
    SENDING_PROCESS,
    DONE,
    CANCELLED,
}
