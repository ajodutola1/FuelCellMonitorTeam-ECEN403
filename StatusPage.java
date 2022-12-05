package com.example.myfirstapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.github.mikephil.charting.charts.BarChart;
import com.github.mikephil.charting.data.BarData;
import com.github.mikephil.charting.data.BarDataSet;
import com.github.mikephil.charting.data.BarEntry;
import com.github.mikephil.charting.interfaces.datasets.IBarDataSet;
import com.github.mikephil.charting.utils.ColorTemplate;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


public class StatusPage extends AppCompatActivity {

    BarChart barChart;
    ArrayList<String> fuelCells = new ArrayList<>();
    ArrayList<Float> voltages = new ArrayList<Float>();
    ArrayList<BarEntry> barEntries;
    BarDataSet barDataSet;
    BarData barData;

    private DatabaseReference databaseRef;
    private FirebaseDatabase database = FirebaseDatabase.getInstance();
    private Button returnHome;
    private List<FuelCell> fuelCell = new ArrayList<>();
    private float voltageLevel1;
    FuelCellInformation fc1Info = new FuelCellInformation();
    private static final String TAG = "Array Test";
    String fc1Alert;
    String fc1Date;
    String fc1Voltage;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_status_page);

        returnHome = (Button) findViewById(R.id.returnHomeFromStatus);
        returnHome.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openHome();
            }
        });

        //read info from database
        databaseRef = database.getReference("fuelcells");
        DatabaseReference fuelCell1Ref = databaseRef.child("fuelcell1");
        fuelCell1Ref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if (snapshot.exists()) {
                    for (DataSnapshot ds : snapshot.getChildren()) {
                        //FuelCellInformation fc1Info = new FuelCellInformation();
                        fc1Alert = ds.getValue(String.class);
                        //fc1Info.setAlert(ds.child("alert").getValue(FuelCellInformation.class).getAlert());
                        fc1Date = ds.getValue(String.class);
                        fc1Voltage = ds.getValue(String.class);
//                        fc1Info.setDate(ds.child("date").getValue(FuelCellInformation.class).getDate());
//                        fc1Info.setVoltageLevel(ds.child("voltageLevel").getValue(FuelCellInformation.class).getVoltageLevel());
                    }
                    //voltageLevel1 = Float.parseFloat(fc1Voltage);
                }
                voltageLevel1 = Float.valueOf(fc1Voltage);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Log.w(TAG, "Failed to read value.", error.toException());
            }
        });


        fuelCells.add("Fuel Cell 1");
        fuelCells.add("Fuel Cell 2");
        fuelCells.add("Fuel Cell 3");
        fuelCells.add("Fuel Cell 4");
        fuelCells.add("Fuel Cell 5");
        fuelCells.add("Fuel Cell 6");
        fuelCells.add("Fuel Cell 7");
        fuelCells.add("Fuel Cell 8");
        fuelCells.add("Fuel Cell 9");
        fuelCells.add("Fuel Cell 10");
        fuelCells.add("Fuel Cell 11");
        fuelCells.add("Fuel Cell 12");
        fuelCells.add("Fuel Cell 13");
        fuelCells.add("Fuel Cell 14");
        fuelCells.add("Fuel Cell 15");
        fuelCells.add("Fuel Cell 16");

        barChart = (BarChart) findViewById(R.id.status_page);
        barEntries = new ArrayList<>();
        barEntries.add(new BarEntry(1.5f, 1));
        barEntries.add(new BarEntry(0.5f, 2));
        barEntries.add(new BarEntry(1.5f, 3));
        barEntries.add(new BarEntry(2f, 4));
        barEntries.add(new BarEntry(1.75f, 5));
        barEntries.add(new BarEntry(1.5f, 6));
        barEntries.add(new BarEntry(1f, 7));
        barEntries.add(new BarEntry(1f, 8));
        barEntries.add(new BarEntry(0.6f, 9));
        barEntries.add(new BarEntry(1.4f, 10));
        barEntries.add(new BarEntry(0.9f, 11));
        barEntries.add(new BarEntry(1.8f, 12));
        barEntries.add(new BarEntry(1.2f, 13));
        barEntries.add(new BarEntry(0.75f, 14));
        barEntries.add(new BarEntry(0.4f, 15));
        barEntries.add(new BarEntry(1.1f, 16));

        barDataSet = new BarDataSet(barEntries, "Fuel Cells");
        barDataSet.setColors(ColorTemplate.LIBERTY_COLORS, 255);
        barDataSet.setValueTextColor(0);
        barData = new BarData(fuelCells, barDataSet);
        barChart.setData(barData);
        barChart.setDescription("Status of Fuel Cells");
        barChart.setTouchEnabled(true);
        barChart.setDragEnabled(true);
        barChart.setScaleEnabled(true);
    }

    public void openHome(){
        Intent intent = new Intent(this, Dashboard.class);
        startActivity(intent);
    }

}