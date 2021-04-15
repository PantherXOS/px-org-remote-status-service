(use-modules
  (guix build-system cmake)
  (guix download)
  (guix packages)
  (gnu packages compression)
  (gnu packages curl)
  (gnu packages pkg-config)
  (gnu packages serialization)
  (gnu packages sqlite)
  (guix gexp)
  (px packages common)
  (px packages monitoring)
  ((guix licenses) #:prefix license:))


(define-public px-org-remote-status-service
  (package
    (name "px-org-remote-status-service")
    (version "0.1.4")
    (source (local-file (canonicalize-path ".")
              #:recursive? #t))
    (build-system cmake-build-system)
    (arguments
        `(
           #:tests? #f
;           #:phases
;           (modify-phases %standard-phases
;             (add-after 'unpack 'fix-source
;               (lambda _
;                 (chdir "../")
;               )))
         ))
    (inputs `(
               ("sqlite", sqlite)
               ("curl", curl)
               ("restclient-cpp", restclient-cpp)
               ("zlib", zlib)
               ("yaml-cpp", yaml-cpp)
               ("capnproto", capnproto)))
    (native-inputs `(
                      ("pkg-config", pkg-config)
                    ))
    (propagated-inputs `(
                          ("monit", monit)))

    (home-page "https://www.pantherx.org/")
    (synopsis "PantherX Remote Status Monitoring Service")
    (description "This package provides background services to show status ")
    (license license:expat)))


px-org-remote-status-service