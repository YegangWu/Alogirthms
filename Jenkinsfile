pipeline {
    agent any
    stages {
	stage('Build') {
	    steps {
		echo 'Building...'
		dir("src") {
		    sh "make clean"
		    sh "make"
		}
	    }
	}
	stage('Test') {
	    steps {
		echo 'Runing test...'
		dir("src") {
		    sh "./test"
		}
	    }
	}
    }
}
