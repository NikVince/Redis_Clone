pipeline {
    agent any
    
    options {
        // Report status back to GitHub
        // githubSetCommitStatus() // Commented out due to error generation
        // Add timestamps to console logs
        timestamps()
        // Discard old builds, keeping only recent ones
        buildDiscarder(logRotator(numToKeepStr: '10'))
        // Timeout if build takes too long
        timeout(time: 30, unit: 'MINUTES')
    }
    
    stages {
        stage('Checkout') {
            steps {
                // Clean workspace before checkout
                cleanWs()
                checkout scm
                
                // Output git info for debugging
                sh '''
                git branch -v
                git remote -v
                echo "Git commit: ${GIT_COMMIT}"
                echo "Branch name: ${BRANCH_NAME}"
                '''
            }
        }
        
        stage('Configure') {
            steps {
                sh '''
                # Create build directory
                mkdir -p build
                cd build
                
                # Configure with CMake in Debug mode with tests enabled
                cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTING=ON
                '''
            }
        }
        
        stage('Build') {
            steps {
                sh '''
                cd build
                # Build using all available cores
                cmake --build . -- -j$(nproc)
                '''
            }
        }
        
        stage('Test') {
            steps {
                sh '''
                cd build
                # Run tests with verbose output
                ctest -V
                '''
            }
            post {
                // Archive test results if they exist
                always {
                    sh 'find build -name "*.xml" -type f'
                    junit(testResults: 'build/test-*.xml', allowEmptyResults: true)
                }
            }
        }
        
        stage('Static Analysis') {
            parallel {
                stage('Cppcheck') {
                    steps {
                        sh '''
                        # Run cppcheck analysis
                        cppcheck --enable=all --xml --xml-version=2 \
                            --suppress=missingIncludeSystem \
                            --output-file=cppcheck-result.xml src/ 2>/dev/null
                        
                        # Output summary to console
                        echo "Cppcheck summary:"
                        grep -c "error" cppcheck-result.xml || true
                        grep -c "warning" cppcheck-result.xml || true
                        '''
                    }
                    post {
                        always {
                            // Record Cppcheck issues
                            recordIssues(tools: [cppCheck(pattern: 'cppcheck-result.xml')])
                        }
                    }
                }
                
                stage('Compiler Warnings') {
                    steps {
                        sh '''
                        cd build
                        # Rebuild with extra warnings enabled
                        CXXFLAGS="-Wall -Wextra" cmake --build . -- -j$(nproc)
                        '''
                    }
                    post {
                        always {
                            // Record GCC/Clang compiler warnings
                            recordIssues(tools: [gcc()])
                        }
                    }
                }
            }
        }
        
        stage('Memory Check') {
            when {
                // Only run on stable branches or PRs
                anyOf {
                    branch 'test'
                    branch 'main'
                }
            }
            steps {
                sh '''
                cd build
                # Find the test executables
                find . -type f -executable -name "test_*" > executables.txt
                
                # Run Valgrind on each executable
                if [ -s executables.txt ]; then
                    while IFS= read -r exe; do
                        echo "Running Valgrind on $exe"
                        valgrind --leak-check=full --show-leak-kinds=all \
                            --track-origins=yes --xml=yes \
                            --xml-file="$(basename "$exe")-valgrind.xml" \
                            "$exe"
                    done < executables.txt
                else
                    echo "No test executables found"
                fi
                '''
            }
            post {
                always {
                    // Record Valgrind issues
                    recordIssues(tools: [valgrind(pattern: 'build/*-valgrind.xml')])
                }
            }
        }
        
        stage('Merge to Main') {
            when {
                allOf {
                    // Only run on test branch
                    branch 'test'
                    // Only when the build is successful
                    expression { currentBuild.resultIsBetterOrEqualTo('SUCCESS') }
                }
            }
            steps {
                // Use withCredentials to securely handle GitHub credentials
                withCredentials([usernamePassword(credentialsId: 'github-auth', 
                                passwordVariable: 'GIT_PASSWORD', 
                                usernameVariable: 'GIT_USERNAME')]) {
                    sh '''
                    # Configure Git user identity for the merge
                    git config user.name "Jenkins"
                    git config user.email "jenkins@example.com"
                    
                    # Fetch latest from origin
                    git fetch origin main:refs/remotes/origin/main
                    
                    # Try to merge - if it fails, the script will exit with error
                    echo "Attempting to merge ${GIT_COMMIT} to main branch"
                    git checkout -b main origin/main
                    git merge --ff-only ${GIT_COMMIT}
                    
                    # Push to main with credentials
                    echo "Pushing to main branch"
                    git push https://${GIT_USERNAME}:${GIT_PASSWORD}@github.com/NikVince/Redis_Clone.git HEAD:main
                    '''
                }
            }
        }
    }
    
    post {
        always {
            // Clean workspace after build
            cleanWs(cleanWhenNotBuilt: false,
                    deleteDirs: true,
                    disableDeferredWipeout: true,
                    notFailBuild: true,
                    patterns: [[pattern: 'build/', type: 'INCLUDE']])
        }
        success {
            echo 'Build successful!'
            // Additional success actions like notifications could go here
        }
        failure {
            echo 'Build failed!'
            // Additional failure actions could go here
        }
    }
}
