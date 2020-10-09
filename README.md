
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![GPL License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]


<br />
<p align="center">
  <a href="https://github.com/clovrlabs/awemaria-plugin">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Awemaria Plugin</h3>
MariaDB's data-at-rest encryption requires the use of a key management and encryption plugin. 
These plugins are responsible both for the management of encryption keys and for the actual encryption and decryption of data. 

However this plugin come with some limitations.

You are bound to trust your operators when it comes to encryption, and often in regulated environment
where separation of privileges is paramount that's not always possible.

With Awemaria the shamir's secret sharing is used, therefore securing a secret in a distributed way. 
The secret is split into multiple parts, called shares. These shares are used to reconstruct the original secret.

To unlock the secret via Shamir's secret sharing, you need a minimum number of shares. This is called the threshold, and is used to denote the minimum number of shares needed to unlock the secret. Let us walk through an example:

  <p align="center">
    <br />
    <a href="https://github.com/clovrlabs/awemaria"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/clovrlabs/awemaria">View Demo</a>
    ·
    <a href="https://github.com/clovrlabs/awemaria/issues">Report Bug</a>
    ·
    <a href="https://github.com/clovrlabs/awemaria/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project

[![awemaria logo][product-screenshot]](https://awemaria.clovrlabs.com)

Some of the useful properties of Awemaria Shamir's scheme are:

    Secure: Information theoretic security.
    Minimal: The size of each piece does not exceed the size of the original data.
    Extensible: When k {\displaystyle k\,\!} k\,\! is kept fixed, D i {\displaystyle D_{i}\,\!} D_i\,\! pieces can be dynamically added or deleted without affecting the other pieces.
    Dynamic: Security can be easily enhanced without changing the secret, but by changing the polynomial occasionally (keeping the same free term) and constructing new shares to the participants.
    Flexible: In organizations where hierarchy is important, we can supply each participant different number of pieces according to their importance inside the organization. For instance, the president can unlock the safe alone, whereas 3 secretaries are required together to unlock it.


## MariaDB: The open source relational database 

MariaDB was designed as a drop-in replacement of MySQL(R) with more
features, new storage engines, fewer bugs, and better performance.

MariaDB is brought to you by the MariaDB Foundation and the MariaDB Corporation.
Please read the CREDITS file for details about the MariaDB Foundation,
and who is developing MariaDB.

MariaDB is developed by many of the original developers of MySQL who
now work for the MariaDB Corporation, the MariaDB Foundation and by
many people in the community.

MySQL, which is the base of MariaDB, is a product and trademark of Oracle
Corporation, Inc. For a list of developers and other contributors,
see the Credits appendix.  You can also run 'SHOW authors' to get a
list of active contributors.

A description of the MariaDB project and a manual can be found at:

https://mariadb.org



## Getting Started


### Prerequisites


### Installation




## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://awemaria.docs.clovrlabs.net)_



## Roadmap

See the [open issues](https://github.com/clovrlabs/awemaria-plugin/issues) for a list of proposed features (and known issues).



## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/somefeature`)
3. Commit your Changes (`git commit -m 'Add somefeature'`)
4. Push to the Branch (`git push origin feature/somefeature`)
5. Open a Pull Request



## License

Distributed under the GPL License. See `LICENSE` for more information.


NOTE: 

MariaDB is specifically available only under version 2 of the GNU
General Public License (GPLv2). (I.e. Without the "any later version"
clause.) This is inherited from MySQL. Please see the README file in
the MySQL distribution for more information.

License information can be found in the COPYING file. Third party
license information can be found in the THIRDPARTY file.


## Contact

Your Name - [@clovrlabs](https://twitter.com/clovrlabs) - info@clovrlabs.com

Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)



## Acknowledgements
* [mariadb](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Choose an Open Source License](https://choosealicense.com)


[contributors-shield]: https://img.shields.io/github/contributors/clovrlabs/awemaria-plugin.svg?style=flat-square
[contributors-url]: https://github.com/clovrlabs/awemaria-plugin/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/clovrlabs/awemaria-plugin.svg?style=flat-square
[forks-url]: https://github.com/clovrlabs/awemaria-plugin/network/members
[stars-shield]: https://img.shields.io/github/stars/clovrlabs/awemaria-plugin.svg?style=flat-square
[stars-url]: https://github.com/clovrlabs/awemaria-plugin/stargazers
[issues-shield]: https://img.shields.io/github/issues/clovrlabs/awemaria-plugin.svg?style=flat-square
[issues-url]: https://github.com/clovrlabs/awemaria-plugin/issues
[license-shield]: https://img.shields.io/github/license/clovrlabs/awemaria-plugin.svg?style=flat-square
[license-url]: https://github.com/clovrlabs/awemaria-plugin/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/clovrlabs
[product-screenshot]: images/screenshot.png


