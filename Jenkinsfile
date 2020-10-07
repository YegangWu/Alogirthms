pipeline {
	agent any
	stages {
		stage('Stage 1') {
			steps {
				echo 'go to dfs'
				dir("dfs") {
					sh "make clean"
					sh "make"
				}
			}
		}
	}
}
