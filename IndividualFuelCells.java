package com.example.myfirstapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class IndividualFuelCells extends AppCompatActivity {

    private Button returnHome;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_individual_fuel_cells);

        returnHome = (Button) findViewById(R.id.returnHome);
        returnHome.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openHome();
            }
        });
    }

    public void openHome(){
        Intent intent = new Intent(this, Dashboard.class);
        startActivity(intent);
    }
}