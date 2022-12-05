package com.example.myfirstapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class date_input extends AppCompatActivity {

    private Button viewHistorical;
    private Button returnHome;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_date_input);

        viewHistorical = (Button) findViewById(R.id.viewHistoricalGraph);
        returnHome = (Button) findViewById(R.id.returnHomeFromInput);

        viewHistorical.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openHistorical();
            }
        });

        returnHome.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openHome();
            }
        });
    }

    public void openHistorical(){
        Intent intent = new Intent(this, HistoricalTrends.class);
        startActivity(intent);
    }
    
    public void openHome(){
        Intent intent = new Intent(this, Dashboard.class);
        startActivity(intent);
    }
}