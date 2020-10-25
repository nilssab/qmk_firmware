pipeline {
	agent any
	stages {
		stage("build") {
			steps{
				echo "building ${BRANCH_NAME}"
				sh "make keyboard=planck keymap=nisse-default"
			}
		}
	}
}
