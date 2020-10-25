pipeline {
	agent any
	stages {
		stage("build") {
			steps{
				echo "building ${BRANCH_NAME}"
				#sh "apt-get install gcc-avr"
				sh "make keyboard=planck keymap=nisse-default"
			}
		}
	}
}
