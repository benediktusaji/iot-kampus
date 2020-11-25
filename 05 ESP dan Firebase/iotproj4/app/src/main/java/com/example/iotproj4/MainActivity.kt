package com.example.iotproj4

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Switch
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.database.*


class MainActivity : AppCompatActivity() {
    private lateinit var editTextAngel: EditText
    private lateinit var txtLuxValue: TextView
    private lateinit var txtSuhuValue: TextView
    private lateinit var txtKelembababValue: TextView
    private lateinit var switch: Switch
    private lateinit var button: Button
    private lateinit var database: FirebaseDatabase
    private lateinit var reference: DatabaseReference
    private var sistem = true;


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        txtLuxValue = findViewById(R.id.txtLuxValue)
        txtSuhuValue = findViewById(R.id.txtSuhuValue)
        txtKelembababValue = findViewById(R.id.txtKelembabanValue)
        editTextAngel = findViewById(R.id.editTextAngel)
        switch = findViewById(R.id.switch1)
        button = findViewById(R.id.button)
        database= FirebaseDatabase.getInstance()
        reference=database.getReference("node1")

        button.setOnClickListener {
            if(sistem){
                val double1: Double? = editTextAngel.text.toString().toDouble()
                reference.child("servo").setValue(double1)
            }
        }
        switch.showText
        switch.setOnCheckedChangeListener { _, isChecked ->
            val msg = if (isChecked) "ON" else "OFF"
            sistem = isChecked
            reference.child("sistem").setValue(msg)

        }

        // Read from the database
        reference.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                // This method is called once with the initial value and again
                // whenever data at this location is updated.
                txtLuxValue.text = dataSnapshot.child("lux").getValue().toString()
                txtSuhuValue.text = dataSnapshot.child("suhu").getValue().toString()
                txtKelembababValue.text = dataSnapshot.child("kelembaban").getValue().toString()
            }

            override fun onCancelled(error: DatabaseError) {
                // Failed to read value
            }
        })
    }
}