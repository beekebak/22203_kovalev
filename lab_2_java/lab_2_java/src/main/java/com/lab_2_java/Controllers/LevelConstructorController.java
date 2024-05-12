package com.lab_2_java.Controllers;

import com.lab_2_java.Models.ContructorModel;
import com.lab_2_java.Utility.ConstructorTileWrapper;
import com.lab_2_java.Utility.ObservableConstructorTileWrapper;
import com.lab_2_java.Utility.TriCallback;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;

import java.net.URL;
import java.util.*;



public class LevelConstructorController implements Initializable {
    @FXML
    private VBox rightVBox;
    @FXML
    private Label levelNameLabel;
    @FXML
    private TextField levelNameTextField;
    @FXML
    private HBox labelsHBox;
    @FXML
    private HBox textFieldsHBox;
    @FXML
    private Label rowsLabel;
    @FXML
    private Label colsLabel;
    @FXML
    private TextField rowsTextField;
    @FXML
    private TextField colsTextField;
    @FXML
    private ScrollPane tilesMenuScrollPane;
    @FXML
    private GridPane tilesMenuGrid;
    @FXML
    private ScrollPane scrollPane;
    @FXML
    private SplitPane splitPane;
    private GridPane gridView = new GridPane();
    private final ToggleGroup entitySelectButtonsGroup = new ToggleGroup();
    private final ContructorModel model = new ContructorModel(new RegisterCallback());

    @FXML
    private void SaveName(){
        model.getWriter().setFileNameAppendix(levelNameTextField.getText()+".json");
    }

    @FXML
    private void SaveSize(){
        ResizeGridView();
        model.ResizeGrid(Integer.parseInt(rowsTextField.getText()), Integer.parseInt(colsTextField.getText()));
    }

    @FXML
    private void SaveLevel(){
        model.getWriter().ParseLevelConstructorGrid(model.getGrid());
        model.getWriter().Write();
    }

    @FXML
    private void ChangeContent(MouseEvent e){
        model.SetGridCell((int)e.getY()/50, (int)e.getX()/50, model.getCurrentTile());
    }

    public class RegisterCallback implements TriCallback<Void, Integer, Integer,
            List<List<ObservableConstructorTileWrapper>>> {
        @Override
        public Void Apply(Integer i, Integer j, List<List<ObservableConstructorTileWrapper>> grid) {
            Register(i, j, grid);
            return null;
        }
    }

    private void InitializableRadioButtons(){
        int i = 0;
        for(var tile:model.getTilesPool().values()){
            RadioButton button = new RadioButton();
            entitySelectButtonsGroup.getToggles().add(button);
            button.onActionProperty().setValue(event -> model.setCurrentTile(tile));
            tilesMenuGrid.add(new ImageView(tile.getImage()), 0, i);
            tilesMenuGrid.add(button, 1, i);
            i++;
        }
    }

    private void ResizeGridView(){
        gridView = new GridPane();
        while(gridView.getRowCount() < Integer.parseInt(rowsTextField.getText())){
            gridView.getRowConstraints().add(new RowConstraints(50));
        }
        while(gridView.getColumnCount() < Integer.parseInt(colsTextField.getText())){
            gridView.getColumnConstraints().add(new ColumnConstraints(50));
        }
        gridView.setOnMouseClicked(this::ChangeContent);
        gridView.gridLinesVisibleProperty().set(true);
        scrollPane.setContent(gridView);
    }

    private void Register(int i, int j, List<List<ObservableConstructorTileWrapper>> grid){
        ImageView cellView = new ImageView(grid.get(i).get(j).getWrapper().getImage());
        gridView.add(cellView, j, i);
        grid.get(i).get(j).IsNullProperty().addListener(observable -> {
            gridView.getChildren().remove(cellView);
        });
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        levelNameLabel.prefWidthProperty().bind(rightVBox.widthProperty());
        levelNameTextField.prefWidthProperty().bind(rightVBox.widthProperty());
        labelsHBox.prefWidthProperty().bind(rightVBox.widthProperty());
        textFieldsHBox.prefWidthProperty().bind(rightVBox.widthProperty());
        rowsLabel.prefWidthProperty().bind(labelsHBox.widthProperty().divide(2));
        colsLabel.prefWidthProperty().bind(labelsHBox.widthProperty().divide(2));
        rowsTextField.prefWidthProperty().bind(textFieldsHBox.widthProperty().divide(2));
        colsTextField.prefWidthProperty().bind(textFieldsHBox.widthProperty().divide(2));
        tilesMenuScrollPane.prefWidthProperty().bind(rightVBox.widthProperty().divide(4).multiply(3));
        tilesMenuGrid.prefWidthProperty().bind(tilesMenuScrollPane.widthProperty().subtract(100));
        tilesMenuScrollPane.prefHeightProperty().bind(rightVBox.heightProperty().subtract(200));
        while(gridView.getColumnCount() > 0){
            gridView.getColumnConstraints().remove(gridView.getColumnCount()-1);
        }
        while(gridView.getRowCount() > 0){
            gridView.getRowConstraints().remove(gridView.getRowCount()-1);
        }
        InitializableRadioButtons();
    }
}
