
const admin = require('firebase-admin');
const functions = require('firebase-functions');


// Required for side-effects
//require("firebase/firestore");

// // Create and Deploy Your First Cloud Functions
// // https://firebase.google.com/docs/functions/write-firebase-functions
//
// exports.helloWorld = functions.https.onRequest((request, response) => {
//  response.send("Hello from Firebase!");
// });

var firebaseConfig = {
    apiKey: "AIzaSyDVqO_ZosujOi_VjZ2n1Qa5TI1PEF1NNBU",
    authDomain: "espexperiment-bc1a4.firebaseapp.com",
    databaseURL: "https://espexperiment-bc1a4.firebaseio.com",
    projectId: "espexperiment-bc1a4",
    storageBucket: "espexperiment-bc1a4.appspot.com",
    messagingSenderId: "654806948622",
    appId: "1:654806948622:web:19cfd7db045ff4d247555f"
  };
  // Initialize Firebase
admin.initializeApp(firebaseConfig);

var db = admin.firestore();

exports.addUser = functions.https.onRequest(async (req, res) => {
    db.collection("users").add({
        first: req.body.first,
        last: req.body.last,
        born: req.body.born
    })
    .then(function(docRef) {
        res.send("Document written with ID: ");
    })
    .catch(function(error) {
        res.send("Error adding document: ");
    });
  });