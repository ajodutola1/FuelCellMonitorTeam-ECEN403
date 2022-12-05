package com.example.myfirstapp;

public class FuelCellInformation {
    private String voltageLevel;
    private String alert;
    private String date;

    public FuelCellInformation() {

    }

    public String getDate() {
        return date;
    }

    public String getAlert() {
        return alert;
    }

    public void setAlert(String alert) {
        this.alert = alert;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getVoltageLevel() {
        return voltageLevel;
    }

    public void setVoltageLevel(String voltageLevel) {
        this.voltageLevel = voltageLevel;
    }
}
