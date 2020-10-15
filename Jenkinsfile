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
    post {
        success {
            echo 'Success...'
        }
        failure {
            mail to: team@example.com, subject: 'The Pipeline failed :('
        }
    }
}
