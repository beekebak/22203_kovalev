module com.lab_2_java {
    requires javafx.controls;
    requires javafx.fxml;
    requires com.fasterxml.jackson.core;
    requires com.fasterxml.jackson.databind;
    requires org.controlsfx.controls;
    requires java.desktop;

    opens com.lab_2_java to javafx.fxml;
    exports com.lab_2_java;
    opens com.lab_2_java.Levelio to com.fasterxml.jackson.core, com.fasterxml.jackson.databind;
    exports com.lab_2_java.Levelio;
    opens com.lab_2_java.Controllers to javafx.fxml;
    exports com.lab_2_java.Controllers;
}